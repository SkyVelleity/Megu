from twitchio.ext import commands
import threading
import sys
from flask import Flask, request


#
# Config
#

# User defined vars
updatesFilename = 'updates.sky'
chatlogFilename = 'chatlog.txt'
# For external use this needs to be changed from localhost to your IP
serverAddress   = 'localhost'
serverPort      = '8888'

# Command variables
maxx = 31
minx = -30
maxy = 15
miny = -16
maxcol = 65535 # 16 bit in 0x000 to 0xffff
mincol = 0

# Twitch vars
ircToken = '...' # Twitch O-Auth Token
channelName = '...' # Must match O-Auth Token account


#
# Code
#


updatesLog = []

# Simple mutex
isUpdating = False
isSending = False

# Flask code here
app = Flask(__name__)

@app.route('/')
def main():
    return "try /update lol"

@app.route('/cgi-bin/Refresh')
@app.route('/update')
def updates():
    global updatesLog, isUpdating, isSending
    sent = False
    out = "!START\n"
    while sent is False: # Busy wait if race
        if isUpdating is False:
            isSending = True
            print(updatesLog)
            tempUp = updatesLog # Clear the log
            updatesLog = []
            for line in tempUp:
                out += line # Construct this
            isSending = False
            sent = True

    return out # SEND IT

# Send off the total log
@app.route('/cgi-bin/biglog')
@app.route('/biglog')
def biglog():
    with open(updatesFilename, 'r') as f:
        return str(f.read()) # Dump our updates file


#app.run(host='localhost', port='8888') # For debugging in main thread as this is blocking

# Start flask server
th = threading.Thread(target=app.run, args=(serverAddress, serverPort)) # Fire up Flask `file` server 
th.start()


def rgb_hex565(red, green, blue):
    # take in the red, green and blue values (0-255) as 8 bit values and then combine
    # and shift them to make them a 16 bit hex value in 565 format. 
    return "0x%0.4X" % ((int(red / 255 * 31) << 11) | (int(green / 255 * 63) << 5) | (int(blue / 255 * 31)))

# Twitch code here
def parse_draw_command(message):
    coma = str(message).split(' ')

    try:
        print("X RAW: "+coma[1])
        print("Y RAW: "+coma[2])
        print("R RAW: "+coma[3])
        print("G RAW: "+coma[4])
        print("B RAW: "+coma[5])
        x = int(coma[1])
        y = int(coma[2])
        r = int(coma[3])
        g = int(coma[4])
        b = int(coma[5])
        print("X: "+str(x))
        print("Y: "+str(y))
        print("R: "+str(r))
        print("G: "+str(g))
        print("B: "+str(b))

        col = int(rgb_hex565(r, g, b), 16)

        if x > maxx or x < minx or y > maxy or y < miny or col < mincol or col > maxcol:
            raise Exception("Draw values out of range")

        return x, y, col

    except Exception as e:
        print('invalid draw command')
        print(str(e))
        return None, None, None
            
def padhexa(s):
    return '0x' + s[2:].zfill(4)


class Bot(commands.Bot):
    def __init__(self):
        super().__init__(irc_token=ircToken, nick=channelName, prefix='!',
                         initial_channels=[channelName])

    # Events don't need decorators when subclassed
    async def event_ready(self):
        print(f'Ready | {self.nick}')

    async def event_message(self, message):
        print("Got message from twitch chat: "+str(message.content)) 

        log = str(message.author)+": "+str(message.content)+"\n"
        # Dump it to a fat chat log
        with open(chatlogFilename, 'a') as h:
                    h.write(log)

        # If it's a draw command
        if (str(message.content).startswith("!draw")):
            print("Got draw command: "+str(message.content))

            x, y, col = parse_draw_command(message.content)
            
            # If it's a valid command
            if x is not None:
                print("Got valid draw command, updating file!!")
                outLineString = '~'
                outLineString += str(x)
                outLineString += 'x'
                outLineString += str(y)
                outLineString += 'y'
                outLineString += padhexa(str(hex(col)).upper()) # Pad out hex
                outLineString += '\n'

                updated = False
                while updated is False:
                    if isSending is False:
                        isUpdating = True
                        with open(updatesFilename, 'a') as h:
                            h.write(outLineString) # UPDATE BEEG LOGGG
                        updatesLog.append(outLineString) # Update temp array
                        isUpdating = False
                        updated = True

                message.content = "!internal_good" # Hack to let the user know it worked TODO: FIX

            # If it's an invalid command
            else:
                print("Got invalid draw command, telling user they stuffed up!!")
                message.content = "!internal_bad" # Hack to let the user know the stuffed up TODO: FIX



        await self.handle_commands(message) # This code then sends it off to our
                                            # library engine to handle any commands like !help

    # Commands use a different decorator
    @commands.command(name='help')
    async def my_command(self, ctx):
        await ctx.send(f'Hello {ctx.author.name}, you can draw on the screen with !draw :^)!')
        await ctx.send(f'Use !draw x y col_in_hex')
        await ctx.send(f'e.g. !draw 12 14 0xF0F0')

    @commands.command(name='internal_bad')
    async def bad_comm(self, ctx):
        await ctx.send(f'Invalid command {ctx.author.name}, see correct format below, dimensions are x: '+str(minx)+' to '+str(maxx)+' and y: '+str(miny)+' to '+str(maxy)+' :^)!')
        await ctx.send(f'Use !draw x y col_in_hex - can use https://chrishewett.com/blog/true-rgb565-colour-picker/ to get your colours')
        await ctx.send(f'e.g. !draw 12 14 0xF0F0')

    @commands.command(name='internal_good')
    async def good_comm(self, ctx):
        await ctx.send(f'Draw succesful {ctx.author.name}!! The screen will update shortly with your contribution :^)!')


bot = Bot() # Create our bot class

bot.run() # Run our bot class
th.join() # Join our thread

print("Done :^)")