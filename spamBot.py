from twitchio.ext import commands
import time

exampleArray = [

"!draw -32 0 255 255 255", "!draw -31 0 255 255 255", "!draw -30 0 0 0 0", "!draw -29 0 255 255 255", "!draw -28 0 0 0 0", "!draw -27 0 255 255 255", "!draw -26 0 255 255 255", 
"!draw -32 1 255 255 255", "!draw -31 1 0 0 0", "!draw -30 1 0 0 0", "!draw -29 1 255 0 255", "!draw -28 1 0 0 0", "!draw -27 1 0 0 0", "!draw -26 1 255 255 255", 
"!draw -32 2 0 0 0", "!draw -31 2 0 0 0", "!draw -30 2 255 0 0", "!draw -29 2 255 0 255", "!draw -28 2 255 0 0", "!draw -27 2 0 0 0", "!draw -26 2 0 0 0", 
"!draw -32 3 255 255 255", "!draw -31 3 255 0 255", "!draw -30 3 255 0 0", "!draw -29 3 255 0 0", "!draw -28 3 255 0 0", "!draw -27 3 255 0 255", "!draw -26 3 255 255 255", 
"!draw -32 4 0 0 0", "!draw -31 4 0 0 0", "!draw -30 4 255 255 255", "!draw -29 4 255 0 0", "!draw -28 4 255 255 255", "!draw -27 4 0 0 0", "!draw -26 4 0 0 0", 
"!draw -32 5 255 255 255", "!draw -31 5 0 0 0", "!draw -30 5 0 0 0", "!draw -29 5 255 0 255", "!draw -28 5 0 0 0", "!draw -27 5 0 0 0", "!draw -26 5 255 255 255", 
"!draw -32 6 255 255 255", "!draw -31 6 255 255 255", "!draw -30 6 0 0 0", "!draw -29 6 255 255 255", "!draw -28 6 0 0 0", "!draw -27 6 255 255 255", "!draw -26 6 255 255 255" 

]

# api token can be passed as test if not needed.
# Channels is the initial channels to join, this could be a list, tuple or callable
bot = commands.Bot(
    irc_token='  oauth token goes here',
    api_token='test',
    nick=' your accounts name goes here, must match your oauth token',
    #Trigger character, use something weird like ^, for example, with it as is below, "^example" will trigger the bot below
    prefix='^',
    initial_channels=['velleity_grimripper']
)


# Register an event with the bot
@bot.event
async def event_ready():
    print(f'Ready | {bot.nick}')


@bot.event
async def event_message(message):
    print(message.content)

    # If you override event_message you will need to handle_commands for commands to work.
    await bot.handle_commands(message)


# Register a command with the bot

@bot.command(name='example', aliases=['t'])
async def test_command(ctx):
    for x in exampleArray:
    	await ctx.send(x)
    	time.sleep(1)


bot.run()
