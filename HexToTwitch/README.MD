Converts an image created using this:
https://lvgl.io/tools/imageconverter
-to something you can spam in twitch.
Give it your image res in arrayX/arrayY, and the co-ordinates you want for your top right corner

I reccomend using
https://www.pixilart.com/draw#
-to make art, but literally any image fed into the above converter will work.
For now, max you can prrobably do is a 64x32 image, if you set

int startX = -32;

int startY = -16

Once you've got your output, just spam it to twitch chat, newlines are your friend.
Or, alternatively, copy it into an array in spamBot.py, run the bot, and trigger it through chat. 
It tends to hang if you post too much too fast, so lets keep it to 1 post per second, for now at least.


Also, as of now, I'm not sure if it's an issue with my display, but
it only seems to clearly display Primary, Secondary, and Tertiary colours.
Anything that's a mix of R, G, and B tends to wash out into white.
So try to make sure at least one colour is set to 0 (or 0x00) in whatever you send. 
I'll see if I can fix this up when I have a second panel to test with.

