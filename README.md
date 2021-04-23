# Megu

Hacked together from a bunch of other projects, with a handful of support torn out because it was in the way.
Hook up a panel compatible, load this onto an ESP8266, and you're golden.

## Twitch Bot

### Requirements for Twitch Bot
Please run the following commands to install dependencies for TwitchBot: `python3 -m pip install Flask twitchio`

### Setting up Twitch Bot Connection / Token
Please update the variables within the `twitchBot.py` script with your O-Auth token + Channel Name

### Running 
Once setup, you can run the bot with `python3 twitchBot.py`


## Spam Bot
Feel free to use this to spam messages onto my wall, you can also use HexToTwitch to create a nice big array to push.

### SpamBot/HexToTwitch full guide
First, let's get an array using Hex2Twitch
Upload an image, (using the guide below as a reference), into this: https://lvgl.io/tools/imageconverter
Any images will work, but if you don't leave R, G, or B set to zero, you might just end up with a vaugly blue pixel, rather than your desired colour.
Not sure if I'm just handling colours wrong on my end, or if there's a workaround, but keeping colours simple seems to work.
Leave everything default, download the output, then copy the array under the line

/*Pixel format: Blue: 8 bit, Green: 8 bit, Red: 8 bit, Fix 0xFF: 8 bit, */

-into a .h file, like example.h
Update the resolution in example.h so it's correct
Run it and burn it onto an arduino, sue me, would you rather I wrote it in swift?
Check your serial output, you'll now have an array (with maybe an extra comma and quote at the start/end)
Copy it into an array in spamBot.py, there's already an example array filled out.

You'll also need to update spamBot.py with your username and oath token, the latter of which can be obtained here: https://twitchapps.com/tmi/
Save and run with "python3 spamBot.py"
Now try triggering it by sending "^example" in chat
Yeah I'm sure you could just have the script dump the array then termiante, but I'm an idiot.

###Art guide
You can make images suitable here: //https://www.pixilart.com/draw#
Saves you loading up GIMP.
Best if it's pixel art with only Primary, Secondary, and Tertiary colours
Here's a handy reference chart:
![This isn't XKCD lol]https://cdn.sparkfun.com/assets/learn_tutorials/7/1/0/TertiaryColorWheel_Chart.png)
