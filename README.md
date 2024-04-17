![golem_engine_logo_1](./Images/Logo/golem_engine_logo_1.png)

# Golem Engine

This is our game engine. It was made in 4 months by 4 people. The goal of this engine is firstly to learn more about the development of a game engine, but also to add our special touches to it and create custom features we enjoy using and creating. 

**Current version : *BETA***

## Useful links

TDD : https://docs.google.com/document/d/1Jtf2k2K6IGrmmmKho3yW_sFI192x4ObjKjQ_ZNkWz0c/edit?usp=drive_link

Backlogs : https://docs.google.com/spreadsheets/u/0/d/13i5iRtw7TFWCFSN_rtzIWthV1jdXRb6yfZKntQG_MpQ/edit

Trello : https://trello.com/w/golem_engine

Engine UML : https://app.diagrams.net/#G1YYfYapjmPG-OQKQSFgRh9GnygVCJJSjI

Interaction Diagram : https://app.diagrams.net/#G1OdVxF9WFAIje_cibcuFsyLmjxvCg91QG

## Setup

- **Download OpenAL**  
GolemEngine uses OpenAL library so it is necessary to download it on your device. GolemEngine already has OpenAL setup inside it but won't detect it if it isn't installed on your device.  
To Download it, go to https://www.openal.org/downloads/  
![OpenAl1_Image](./Images/Readme/Screenshot_OpenAL_installation_1.png)  
Download the Windows Installer (zip) :  
![OpenAl2_Image](./Images/Readme/Screenshot_OpenAL_installation_2.png)  
Open the .zip file and run the oalinst.exe file.  
Accept everything.  
![OpenAl3_Imagee](./Images/Readme/Screenshot_OpenAL_installation_3.png)  
OpenAL should be correctly installed now.


- **Download the engine**  
Clone the project.  
Open GolemEngine.sln in visual studio 2019.  
Make sure that the project settings C++ norm is 20.  
Set GolemEditor project as start up project.  
Run.  

## Functionalities

Golem Engine includes classical game engine features such as a docked imgui space for a basic actors, viewport, scene graph, debug, inspector and file browser window.  
You can navigate in the viewport using WASD and right click.  
Inspector allows (for now) to modify the transform of various objects and add light components.  

## Special Features

We plan to have several features :  
Map making tool.  
Toon Shading tool.  
Particle System.  

These special features will be developed later.