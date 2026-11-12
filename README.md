### QComponents
###### A Minimal UI library for QML

 Currently, the vast majority of the library is written in QML. However, it is gradually being rewritten to C++. 
 Consequently, The component names, exposed functions, and present variables are bound to change.

 ### How do I include QComponents in my project?

1. Navigate to the Releases section and download the source code zip file I provide.
    + The source code release schedule of QComponents closely mirrors that of my browser project, [FoilBrowser](https://github.com/WhiskerDotDev/FoilBrowser).
2. Unzip the downloaded file, and move it to your project directory, preferably closer to the root of the project
3. Add the following to your CMakeLists.txt:
    ```CMakeLists file
    add_subdirectory("QComponents" QComponentsproj)

    # add this where it makes the most sense:

    target_link_libraries( myProj

    QComponentsprojplugin
    )
    ```
4. In any of your QML files, simply write:
     ```QML
      import QComponents
    ```
