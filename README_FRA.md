<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-Wide.png">
<hr>

## Sommaire

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
Ce "<i>projet</i>" n'a que pour but d'être une "<i>trace</i>" sur mon apprentissage d'un sujet totalement nouveau (du moins pour moi).
Mon but était uniquement d'être capable de rendre un triangle à l'écran au sein d'une <i>PlayStation3</i> afin de mettre en pratique certaines de mes 
"<i>compétences</i>" avec une théorie fraîchement comprises sur le sujet et non pas de développer une application/jeu complet.
Vous pouvez voir ce projet comme une sorte de "preuve" face à ma détermination d'apprendre tout et n'importe quoi.

Le README est pas incroyable, j'ai perdu l'habitude...

Je suis un novice dans ce qui concerne les consoles, leurs contraintes et ce qui suit. Je n'ai qu'une partie théorique.

Ce que j'ai programmé reste une approche extrêmement primitive du <i>PSGL</i> et de la <i>PlayStation3</i> en elle-même.
Il pourrait recevoir beaucoup d'améliorations si je décide de continuer d'en apprendre plus sur l'API.

<strong>Je ne suis pas en possibilité de fournir les <i>SDKs</i>, <i>toolchains</i> ou <i>compilers</i> utilisés.</strong>
</div>
<hr>

<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION02.png" id="background">

<div>
<p>J'ai toujours été vachement curieux de tout ce qui concerne le jeu-vidéo.
J'ai commencé comme beaucoup sur <i>Unity Engine</i> il y a fort longtemps déjà, et mon intérêt s'est 
tourné assez tardivement vers des concepts plus poussés comme par exemple le “<i>rendu 3D en temps-réel</i>”.<br/>

J'ai commencé avec OpenGL, puis DirectX11 et un peu de VULKAN, le tout dans différents langages comme le C++, C# et JAVA.
Du simple rendu d'un cube aux shaders, <i>3rd party libraries</i> comme <i>Dear.ImGUI (FrontEnd)</i>, <i>Bullet (Physics)</i>, ...</p>
</div>

<div>
<p>Ma curiosité s'est portée sur les consoles,
qui sont pour moi 100x fois plus différentes que des machines "<i>desktop-based (PC)</i>", et la <i>PlayStation2</i> a (<i>étrangement</i>) été mon premier choix.</p>

<p>J'avais déjà quelques notions primitives dans ce domaine, et je voulais faire quelque chose de totalement différent sur quelque chose que je n'avais
jamais touché précédemment niveau développement.<br/>
Pour faire simple, la PS2 a été une experience traumatisante, en particulier parce que j'utilisais des <i>SDKs</i>, <i>toolchains</i> et <i>outils</i> développés 
et maintenus par la communauté (<i>de très bon outils, certains limités, mais LARGEMENT au dessus de mes compétences</i>), majoritairement utilisés et discutés
par des développeurs sur des forums pour faire des Homebrews.
Mais j'ai quand-même réussi à faire le rendu d'un cube à partir de ZERO à l'aide de documentation, exemples et peu de tutoriels.</p>
</div>

<div>
<p>C'est un an plus tard que j'ai décidé de réessayer avec une autre PlayStation, la <i>PlayStation3</i>.</p>

<p>Sortie le <i>11 novembre 2006</i> au Japon, y a un bail, elle embarque pleins de trucs qui on la classe: 
le <i>Blu-Ray</i>, <i>SIXAXIS (DualShock3)</i>, <i>1080p60</i>, <i>PSN</i>, <i>CELL</i> et j'en passe.<br/>
Sans parler des nombreuses licences que j'ai découvertes ou même vues pousséees sur la 7ème génération, comme
<i>The Last Of Us, MotorStorm, Max Payne, GTA, BURNOUT, Ratchet & Clank FUTURE, TDU, Red Dead, 
Gran Turismo, LBP, Split/Second, DRIVER</i> et encore, bref, je dérape la.<br/>
<strong>Retour au sujet principal...</strong></p>
</div>
<hr>

<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION03.png" id="the-subject">

<div>
<p>Comme dit au dessus, j'ai une expérience moyenne au possible dans ce domaine, 
c'était que sur des machines <i>desktop-based (PC)</i>, pas des consoles! J'ai donc rapidement commencé à établir les options qui sont à ma disposition.</p>
<strong><i>Gardez en tête que je n'ai pas de DEVKIT/DEVTOOL ou même de REFERENCE TOOL, 
uniquement une <i>PlayStation3 SuperSlim</i> quasiement un-jailbreakable et/ou l'emulation à ma disposition.</i></strong> 
Tester directement sur ma propre PS3 n'est pas non plus impossible, mais juste compliqué et long avec une console
qui freeze ou crash pour le plaisir. L'emulation (RPCS3) était la route à prendre pour rapidement tester/debugger.<br/>
Donc je suis déjà un peu short niveau hardware pour du développement (je trouve).<br/>

<i>UnrealEngine3</i> et <i>Unity5</i> ont eu du support pour la <i>PlayStation3</i>, 
mais non (<i>ce n'est pas vraiment ce que j'aimerais, je veux me défier - faire quelque chose "from scratch"</i>).
Et n'oublions pas que leur support respectif est arrêté depuis vachement longtemps.

Je suis rapidement tombé sur <i>GCM</i> (<i>libgcm</i> - arrivé sur la PS3, suivi de la PS4) 
qui avait l'air bas-niveau et le <i>PSGL</i> (arrivé sur la PS2, suivi de la PS3) qui a quand-même 
l'air d'être l'opposé de <i>GCM</i> en termes de complexité.

Après mes petites recherches, je suis directement allé me procurer le software pour tenter d'en faire quelque chose. 
J'ai réussi à obtenir d'un endroit que je citerais pas, un <i>SDK</i> que je vais également pas citer, pour des raisons "légales" 
(<i>d'une source sûre, ne téléchargez rien d'endroits random je vous en conjure</i>).


Pour commencer mon "voyage", j'ai simplement regardé, testé et lu (beaucoup) de documentation, samples, mais également
des PDF provenant d'universités et des PowerPoints/conférences de développeurs ayant bossé sur la PS3 pour un
peu mieux comprendre son fonctionnement.

J'avais déjà un peu de théorie sur sa structure, mais pas vraiment de pratique, ce dont j'avais térriblement besoin.
Mais c'est aussi bien d'entendre des personnes ayant bossé avec le hardware en lui-même pendant plusieurs années.

Après ça, en me basant sur tout les documents qui j'ai récupéré, j'ai créé un nouveau projet C++, et c'est parti!
Je suis directement allé avec <i>PSGL</i> sans vraiment savoir à quoi m'attendre, et j'ai été agréablement surpris de 
réaliser que le <i>PSGL</i> est (assez littéralement) <i>OpenGL ES</i> en lisant de la documentation spécifique,
donc j'avais déjà la plupart voir tous les concepts de base en tête.
</div>
<hr>

<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION04.png" id="demos">

<div>
L'application en elle-même est super super simple.
Un simple fond gris et un triangle au centre et une couleur pour chaque Vertex qui blend
entre elles (Le point de départ de tout hein!).

Toutes les 180 itérations de la boucle principale de l'app, la forme alterne entre un
triangle et un quad.
Tourne en 1080p60, testé sur ma <i>PlayStation3 SuperSlim</i>.
C'est tout :)

Vous pouvez obtenir la dernière version de l'application dans la catégorie “Release” de cette page GitHub.<br/>
OU SINON! Vous pouvez également [regarder une démo ici!](https://www.youtube.com/watch?v=rQP_tcSHeaE)

<a href="https://www.youtube.com/watch?v=rQP_tcSHeaE" align="center" float="left">
<kbd><img src="https://img.youtube.com/vi/rQP_tcSHeaE/maxresdefault.jpg" width="auto" height="130" align="center"></kbd>
<kbd><img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/TRIANGLE.png" width="auto" height="130" align="center"></kbd>
<kbd><img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/QUAD.png" width="auto" height="130" align="center"></kbd>
</a>

</div>
<hr>
<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION05.png" id="retrospective">

<div>
Voici une petite liste de choses que je ferais différemment si je revenais au début du projet:</div>

<!--ts-->
* <strong>Traiter PSGL "comme" OpenGL</strong>
  * Je suis resté trop longtemps devant la documentation et considairais les deux comme totalement différents.<br/>
    En pratique, c'est comme utiliser <i>OpenGL</i> avec des bindings différents de <i>GLFW</i> ou <i>GLuT</i>.
  
* <strong>Une meilleure structure</strong>
  * C'est pas vraiment un problème pour le moment, étant donné que le but du projet étant de simplement
    faire un rendu primitif, mais la manière dont j'ai fait le rendu des formes (Shapes) est clairement
    pas optimal si j'imaginerais pousser un projet dans ce style.

* <strong>Commentaires</strong>
    * Comme d'habitude, je commente beaucoup mon code. Mais je n'aurais pas du utiliser du <i>XML</i> comme je le fait en <i>C#</i>.<br/>
      Avec mes <i>IDEs</i>, c'est pas si grave, c'est une feature "supportée", mais je doute que Doxygen ou
      un vrai développeur soient très content de voir du XML partout pour commenter du code C++.
    * J'aurais dû utiliser une norme plus appropriée pour mes commentaires en C++.
<!--te-->
<hr>

<img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/PSGLTriangle-SECTION06.png" id="whats-next">

<div>
Pas grand chose je pense...

Vu que j'ai du temps à tuer, je pense peut-être continuer de m'amuser avec la PlayStation3. 
Probablement avec de petites fonctionnalités comme la prise en charge des GamePads, ou même
tout refaire mais en utilisant GCM à place de PSGL.
Et aussi comprendre mieux des concepts comme les PPUs, SPUs, ...

Pas vraiment sur entre tenter un truc plus grand, ou ne rien faire du tout.
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

<p>Ce projet a été développé et compilé sur Windows 10 avec 
JetBrains Rider 2024.3.3 et Visual Studio 2013 ULTIMATE.<br/>
Testé sur une <i>PlayStation3 SuperSlim (Firmware: 4.91)</i>.</p>
<hr>

<div align="center"><img src="https://github.com/RedLinesNT/PSGLTriangle/blob/main/assets/logo_FAT2006.png" height="20" width="auto"></div>
