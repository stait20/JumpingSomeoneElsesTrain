# JumpingSomeoneElsesTrain

## EE273 - Group 34
## Created by Frazer Murray and Sam Tait


Compilation Instructions:

Compiling this program requires having an installation of wxWidgets, for a visual walk through use this [Youtube link](https://youtu.be/FOIbK4bJKS8?t=640). below which should start at the specified time stamps [10:40] - [21:00].

However we will include a written guide

1. Go to the wxWdigets [download page](https://www.wxwidgets.org/downloads/).
2. Select Windows ZIP under the source code heading
3. Unzip these files into a new folder (for this guide C:\sdks\wxWidgets is used as an example)
4. Navigate to msw within the build file and open the visual studio solution for the latest version, wx_vc16.sln (C:\sdks\wxWidgets\build\msw\wx_vc16.sln)
5. When opening in visual studio click ok on the security warning
6. Click on "Build" on the top bar, then select "Batch Build..."
7. On the screen that appears click "Select All", and then click "Build"
8. This process will take a while to complete
9. If there are any errors that something has not build, redo steps 6 and 7
10. Now an enviroment variable needs to be added, in the windows search bar, search for "environment variable"
11. Select "Edit the system environment variables"
12. On the screen that appears select "Environment Variables..."
13. Select "New..." under "System variables"
14. Make the variable name WXWIN and the value the installation location (C:\sdks\wxWidgets)
15. Click OK and apply the changes

Now the program should be able to compile in visual studio, the project files are already set up to search in the location described by the environment variable, so no further changes should be required within visual studio
