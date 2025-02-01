<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-Wide.png">
<hr>

<i>Une version Fraçaise est [disponible ici!](https://github.com/RedLinesNT/PSGLTriangle/blob/main/README_FRA.md)</i>

## Summary

<!--ts-->
* [Disclaimer](#disclaimer)
* [Background of the project](#background)
* [Starting everything up](#the-subject)
* [The app in itself / demos](#demos)
* [Retrospective](#retrospective)
* [What's next?](#whats-next)
* [Project information](#project-information)
<!--te-->
<hr>

<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION01.png" id="disclaimer">

<div>
This "<i>project</i>" is only intended to be a "<i>trace</i>" of myself learning a subject totally new (at least to me).
My goal was only to be able to render a triangle on a screen within the <i>PlayStation3</i> to apply my freshly learned "<i>skills</i>" 
on the subject and not to develop an entire application/game.
You can see this project as my determination to learn whatever and everything, if you want. :)

The README could be better, I'm not quite used to make them, it's been a long time...

I'm a neybie yhen it comes to consoles, their constraints and the rest about them. I only have some basic theory.

What I've programmed is an extremely primitive approach to <i>PSGL</i> and the <i>PlayStation3</i> in itself.
It could use a lot of improvement with a little more learning on my part.

<strong>I'm not able to provide the <i>SDKs</i>, <i>toolchains</i> or <i>compilers</i> used.</strong>
</div>
<hr>

<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION02.png" id="background">

<div>
<p>I've always been curious about everything and anything to do with video games. 
I started out simply on <i>Unity Engine</i> a long time ago, and my interest later turned 
to more complicated concepts such as “<i>real-time 3D rendering</i>” (if you can even call it that).<br/>

I started with OpenGL, then DirectX11 and a bit of VULKAN, all of them in various languages such as C++, C# and JAVA. 
From simple cube rendering to shaders, 3rd party libraries like <i>Dear.ImGUI (FrontEnd)</i>, <i>Bullet (Physics)</i>, ...</p>
</div>

<div>
<p>I wanted to push my curiosity onto consoles, 
which for me are 100x times more different than "<i>desktop-based systems</i>", and the <i>PlayStation2</i> (<i>oddly</i>) was my first choice.</p>

<p>I already had some primitive knowledge in the domain, and I wanted to do something brand new with something I've never touch before development-wise.<br/>
To put it simply, the PS2 was quite of a traumatic learning experience, especially as I was using <i>SDKs</i>, <i>toolchains</i> and <i>tools</i> developed 
and maintained by the community (<i>very good tools, some of them limited, but far beyond my skill level</i>), mainly used and talked about by devs on forums
to make homebrews.
But I still managed to render a cube from ZERO with tutorials, docs and samples.</p>
</div>

<div>
<p>It was only a year later that I decided to try again with another PlayStation, the <i>PlayStation3</i>.</p>

<p>Released on <i>November 11, 2006</i> in Japan, quite a long time ago, it packs a lot of cool stuff: 
<i>Blu-Ray</i>, <i>SIXAXIS (DualShock3)</i>, <i>1080p60</i>, <i>PSN</i>, <i>CELL</i> and so on.<br/>
Not to mention the many licenses I've discovered or even seen being pushed on the 7th Generation, 
like <i>The Last Of Us, MotorStorm, Max Payne, GTA, BURNOUT, Ratchet & Clank FUTURE, TDU, Red Dead, 
Gran Turismo, LBP, Split/Second, DRIVER</i> and more, anyway, I'm getting off track, aren't I?<br/>
<strong>Anyway, back to the point.</strong></p>
</div>
<hr>

<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION03.png" id="the-subject">

<div>
<p>As I said above, I have average experience at best in this area, 
but it was all on <i>desktop-based systems</i>, not consoles! So I've begun investigating my available options.</p>
<strong><i>Keep in mind that I don't have a DEVKIT/DEVTOOL or a REFERENCE TOOL, 
only an almost un-jailbreakable <i>PlayStation3 SuperSlim</i> and/or emulation available.</i></strong> 
Testing directly into my own PS3 isn't impossible, just very long and complicated with the console
 freezing or crashing. Emulation (RPCS3) was my way to quickly test everything up.
So I'm already quite short of hardware when it comes to development (I think).<br/>

<i>UnrealEngine3</i> and <i>Unity5</i> had once support for <i>PlayStation3</i>, 
but no (<i>it's not quite what I'd like, I want to challenge myself - Doing something "from scratch"</i>).
And let's not forget that their respective supports ended a LONG time ago.

I quickly came across <i>GCM</i> (<i>libgcm</i> - implemented on PS3, followed on PS4) 
which looks low-level and <i>PSGL</i> (implemented on PS2, followed on PS3) which appears to be 
the opposite of GCM in terms of complexity.

After my little research, I went straight to looking for software to try and hopefully make something out of it. 
I managed to obtain from a place I won't name, an <i>SDK</i> I won't name either, for legal reasons (<i>safely of course, 
please don't download anything from random places I beg you</i>).


To start my "journey" I simply looked, tested and read (a lot) of documentation, samples,
but also PDFs from universities and developer's PowerPoints/conferences who worked on PS3 games 
to better understand how the console works.

I already had a little theory about its structure, but no practice, which is what I needed afterall,
but it's also great to hear about people who really interacted with the hardware for years.

Then based on these documents I made a new C++ project, and the adventure began.
I had blindly gone straight to the <i>PSGL</i> not knowing what to expect, then I was pleasantly 
surprised to realize that the <i>PSGL</i> is simply <i>OpenGL ES</i> by reading further documentation, 
so I already had most if not all the basic concepts already in mind.
</div>
<hr>

<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION04.png" id="demos">

<div>
The application itself is very, very simple.
A simple grey background, a triangle in the center and a color for each Vertex that blends in between
(the starting point of everything I guess).

Every 180 loop-iteration, the shape alternates between a triangle and a quad.
Running 1080p60, tested on my retail <i>PlayStation3 SuperSlim</i>.
That's all :)

You can get the latest version of the application in the “Release” category of this GitHub page.<br/>
Or you can [watch a demonstration here!](https://www.youtube.com/watch?v=rQP_tcSHeaE)

<a href="https://www.youtube.com/watch?v=rQP_tcSHeaE" align="center" float="left">
<kbd><img src="https://img.youtube.com/vi/rQP_tcSHeaE/maxresdefault.jpg" width="auto" height="130" align="center"></kbd>
<kbd><img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/TRIANGLE.png" width="auto" height="130" align="center"></kbd>
<kbd><img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/QUAD.png" width="auto" height="130" align="center"></kbd>
</a>

</div>
<hr>
<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION05.png" id="retrospective">

<div>
Here's a short list of things I would do differently if I were back at the start of the project:</div>

<!--ts-->
* <strong>Treat PSGL more like OpenGL</strong>
  * I've been sitting in front of the documentation for too long, and treating the two as totally different.<br/>
    In practice, it's like using <i>OpenGL</i> with different bindings than <i>GLFW</i> or <i>GLuT</i>.
  
* <strong>An improved structure</strong>
  * It's not really a problem for now, given that my objective was simply to make a very 
    primitive rendering, but way I did the shapes' rendering in the code are 
    really not that great I think.

* <strong>Comments</strong>
    * As usual, I comment a lot on my code. But I shouldn't have used <i>XML</i> like I do in <i>C#</i>.<br/>
      With my <i>IDEs</i>, it's not that bad, it's a "supported" feature, but I doubt that tools like Doxygen 
      or a real developer would be very happy to see XML everywhere to comment C++ code.
    * I should have used a more suitable standard for my comments with C++.
<!--te-->
<hr>

<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION06.png" id="whats-next">

<div>
Not much, I think.

Since I've got some time to kill, I'm thinking of continuing to experiment with the PlayStation3. 
Probably with small features like gamepad support, or even redoing the whole thing but with GCM (the PSGL equivalent).
And also maybe learn a bit more concepts like PPUs, SPUs, ...

I'm not sure whether I'll try to make something a bit bigger or do nothing ahahah.
</div>
<hr>
<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION07.png" id="project-information">
<table>
    <tr>
        <td>Platform Toolset</td>
        <td>PPU SNC</td>
    </tr>
    <tr>
        <td>Output</td>
        <td>*.ppu.self (Fake Signed ELF)</td>
    </tr>
    <tr>
        <td>C++ Language</td>
        <td>C++ 11</td>
    </tr>
</table>

<p>This project was developed and compiled on Windows 10 using 
JetBrains Rider 2024.3.3 and Visual Studio 2013 ULTIMATE.<br/>
Tested on a <i>PlayStation3 SuperSlim (Firmware: 4.91)</i>.</p>
<hr>

<div align="center"><img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/logo_FAT2006.png" height="20" width="auto"></div>
