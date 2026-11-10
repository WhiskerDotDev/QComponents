import QtQuick;

BorderImage{
id: root;

required property rect borders; //We need to make a function that returns a safe, guaranteeably usable Rect.
// Do this in C++

property alias bounds: root.borders;
property alias src: root.source;
width: parent.width; height: parent.height;
smooth: false; antialiasing: false;
cache:true; asynchronous: true;
retainWhileLoading: false;
horizontalTileMode: BorderImage.Repeat; verticalTileMode: BorderImage.Repeat;

border{
top: root.borders.y; // [0]
left: root.borders.x; // [1]
right: root.borders.width; // [2]
bottom: root.borders.height; // [3]
}

// Use "frameCount" as a "feature level"

// We may need to use source size too...

}