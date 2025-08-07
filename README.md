<a id="readme-top"></a>

<!-- PROJECT LOGO -->
<div align="center">
 <img width="1680" height="200" alt="Banner" src="https://github.com/user-attachments/assets/7181667e-e391-430c-80f4-e71a5b2911ce" />
</div>

<br>
  <details>
    <summary>Table of Contents</summary>
    <ol>
      <li>
        <a href="#about-the-project">About The Project</a>
        <ul>
          <li><a href="#built-with">Built With</a></li>
        </ul>
      </li>
      <li>
        <a href="#getting-started">Getting Started</a>
        <ul>
          <li><a href="#prerequisites">Prerequisites</a></li>
          <li><a href="#installation">Installation</a></li>
        </ul>
      </li>
      <li><a href="#contributing">Contributing</a></li>
      <li><a href="#contact">Contact</a></li>
    </ol>
  </details>


<!-- ABOUT THE PROJECT -->
## About The Project

Obstacle Course Racing Game is a simple 3D driving game where you control a car through a looping track filled with obstacles. This project demonstrates basic 3D graphics techniques like modeling, texturing, and lighting in a playable format. Perfect for learning game development fundamentals!

<img width="1409" height="1413" alt="Screenshots" src="https://github.com/user-attachments/assets/2764d4ca-8ed1-414e-afc9-1df0bfdd7823" />

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=for-the-badge&logo=opengl)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

Make sure you have the following installed on your system:

1. C++ Compiler
   - [Visual Studio](https://visualstudio.microsoft.com/vs/community/)
2. freeglut Library
   - [freeglut](https://freeglut.sourceforge.net/index.php#download)
3. Git (for cloning the repository)
   - [Download Git](https://git-scm.com/)

### Installation

1. Clone the repository:

```bash
git clone https://github.com/slooonya/obstacle-course-racing-game.git
```

2. Navigate to the project directory:

```bash
cd Obstacle-Course-Racing-Game
```

3. Set up freeglut (this one is painful)
   - Go to solution properties
   - Click the symbol ‘v’ beside the ‘Platform’, choose ‘x64’
  
   - Click ‘VC++ Directories’ on the left side, then the symbol ‘v’ which is on the right side of ‘Include Directories’, and choose the ‘<Edit...>’ in the list. Press the ‘New Line’ button and choose the ‘include’ folder of the freeglut zip downloaded. Click the ‘OK’ button, to go back to the previous page.
  
   -  Click symbol ‘v’ on the right side of ‘Library Directories’ (blue arrow), and choose ‘<Edit...>’ in the list. Press the ‘New Line’ button (red arrow), and choose the ‘lib’ folder of the freeglut zip downloaded. Click the ‘OK’ button, to go back to the previous page.
  
   -  Click the symbol ‘>’ which is on the left side of ‘Linker’, and choose ‘Input’ in the list of ‘Linker’. Add the text "freeglut_static.lib;" into ‘Additional Dependencies’
  
   -  Click the ‘>’ symbol which is on the left side of ‘Manifest Tool’, and choose ‘Input and Output’ in the list of ‘Manifest Tool’; Set ’Embed Manifest’ to ‘No’; Click ‘OK’.


<br>
<b>Note:</b> If you are just curious about the game you can run the x64/Debug/Obstacle-Course-Racing-Game.exe file!

   

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

Sonya's email address: snmmnva@gmail.com

Project Link: [https://github.com/slooonya/Obstacle-Course-Racing-Game](https://github.com/slooonya/Obstacle-Course-Racing-Game)

<img width="1680" height="200" alt="Footer" src="https://github.com/user-attachments/assets/fcac2301-9e01-4f1f-b6a2-3c49c0fe8ff6" />

<p align="right">(<a href="#readme-top">back to top</a>)</p>
