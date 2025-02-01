# PSGLTriangle
Just me trying to draw a triangle on a PlayStation3 using PSGL.
<hr>

## Summary

<!--ts-->
* [Disclaimer](#disclaimer)
* [Background of the project](#background)
* [Starting everything up](#the-subject)
* [The app in itself / demos](#the-application--demos)
* [Retrospective](#retrospective)
* [What's next?](#whats-next)
* [Project information](#project-information)
<!--te-->
<hr>

## Disclaimer

<div>
This "<i>project</i>" is only intended to be a mark of learning on a subject that is totally new to me.
My goal was only to be able to render a triangle on a screen within a PlayStation3 to apply my learning 
on the subject and not to develop an entire application/game.
You can see this project as my determination to learn whatever and everything if you want. :)

What I've programmed is an extremely primitive approach to PSGL and the PlayStation3 in itself.
It could use a lot of improvement with a little more learning on my part.

<strong>I'm not able to provide the SDKs, toolchains or compilers used.</strong>
</div>
<hr>

## Background

<div>
<p>I've always been curious about everything and anything to do with video games. 
I started out simply on <i>Unity Engine</i> a long time ago, and my interest later turned 
to more complicated concepts such as “<i>real-time 3D rendering</i>” (if you can even call it that).<br/>

I started with OpenGL, then DirectX11 and a bit of VULKAN, all of them in various languages such as C++, C# and JAVA. 
From simple cube rendering to shaders, 3rd party libraries like <i>Dear.ImGUI (FrontEnd)</i>, <i>Bullet (Physics)</i>, ..</p>
</div>

<div>
<p>I wanted to push my curiosity onto consoles, 
which for me are 100x times more different than "<i>desktop-based systems</i>", and the PlayStation2 (<i>oddly</i>) was my first choice.</p>

<p>I already had some primitive knowledge in the domain, and I wanted to do something brand new with something I had never done before.<br/>
To put it simply, the PS2 was a traumatic learning experience, especially as I was using SDKs, toolchains and tools developed 
and maintained by the community (<i>very good tools, some of them limited, but far beyond my skill level</i>). 
But I still managed to render a cube from ZERO with tutorials, docs and samples.</p>
</div>

<div>
<p>It was only a year later that I decided to try again with another PlayStation, the PlayStation3.</p>

<p>Released on <i>November 11, 2006</i>, in Japan. It packs a lot of cool stuff: 
<i>Blu-Ray</i>, <i>SIXAXIS (DualShock3)</i>, <i>1080p60</i>, <i>PSN</i>, <i>CELL</i> and so on.<br/>
Not to mention the many licenses I've discovered or even seen being pushed on the 7th Generation, 
like <i>The Last Of Us, MotorStorm, Max Payne, GTA, BURNOUT, Ratchet & Clank FUTURE, TDU, Red Dead, 
Gran Turismo, LBP, Split/Second, DRIVER</i> and more, anyway, I'm getting off track, aren't I?<br/>
<strong>Anyway, back to the point.</strong></p>
</div>
<hr>

## The Subject

<div>
<p>As I said above, I have at best average experience in this area, 
but it was all on desktop-based systems, not consoles! So I've begun investigating the available options.</p>
<strong><i>Bear in mind that I don't have a DEVKIT/DEVTOOL or a REFERENCE TOOL, 
only an almost un-jailbreakable PlayStation3 SuperSlim and/or emulation available.</i></strong>
So I'm already quite short of hardware when it comes to development (I think).<br/>

UnrealEngine3 and UnityEngine5 had support for PlayStation3, 
but no (<i>it's too easy and not what I'd like, I want to challenge myself - Doing something "from scratch"</i>).
And let's not forgot that their respective supports ended a LONG time ago.

I quickly came across <i>GCM</i> (libgcm - implemented on PS3, followed on PS4) 
which looks low-level and <i>PSGL</i> (implemented on PS2, followed on PS3) which appears to be 
the opposite of GCM in terms of complexity.

After my little research, I went straight to looking for software to try and make something out of it. 
I managed to obtain from a place I won't name, an <i>SDK</i> I won't name either, for legal reasons (<i>safely of course, 
please don't download anything from random places I beg you</i>).


To start my learning, I simply looked, tested and read (a lot) of documentation, samples,
but also PDFs from universities or conferences and developer's PowerPoints who worked on PS3 games 
to better understand how the console works. 

I already had a little theory about its structure, but no practice, which is what I needed.

Then based on these documents I made a new C++ project, and the adventure began.
I had blindly gone straight to the <i>PSGL</i> not knowing what to expect, then I was pleasantly 
surprised to realize that the <i>PSGL</i> is simply <i>OpenGL ES</i>, so I already have all the concepts already in mind.
</div>
<hr>

## The Application / Demos

<div>
The application itself is very, very simple.
A simple grey background, a triangle in the center and a color for each Vertex that blends in between
(the starting point of everything I guess).

Every 180 frames, the shape alternates between a triangle and a quad.
Running 1080p60, tested on a retail PlayStation3 SuperSlim.
That's all :)

You can get the latest version of the application in the “Release” category of this GitHub page.
Or you can watch a demonstration here! <strong>//TODO IMPLEMENT YT DEMO</strong>
</div>
<hr>

## Retrospective

<div>
Here's a short list of things I would do differently if I were back at the start of the project:</div>

<!--ts-->
* <strong>Treat PSGL more like OpenGL</strong>
  * I've been sitting in front of the documentation for too long, and treating the two as totally different.<br/>
    In practice, it's like using OpenGL with different bindings than GLFW or GLuT.
  
* <strong>An improved structure</strong>
  * It's not really a problem, given that my objective was simply to make a very 
    primitive rendering, but way I did the shapes' rendering in the code are 
    really not that great I think.

* <strong>Comments</strong>
    * As usual, I comment a lot on my code. But I shouldn't have used XML like I do in C#.<br/>
      With my IDEs, it's not that bad, it's a supported feature, but I doubt that tools like Doxygen 
      or a real developer would be very happy to see XML everywhere. 
    * I should have used a more suitable standard for my comments with C++.
<!--te-->
<hr>

## What's next?

<div>
Not much, I think.

Since I've got some time to kill, I'm thinking of continuing to experiment with the PlayStation3. 
Probably with small features like gamepad support, or even redoing the whole thing but with GCM (the PSGL equivalent).

I'm not sure whether I'll try to make something a bit bigger or do nothing ahahah.
</div>
<hr>

## Project information
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
JetBrains Rider 2024.3.3 and Visual Studio 2013 ULTIMATE.</p>
<hr>

<div align="center"><img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/logo_FAT2006.png"></div>