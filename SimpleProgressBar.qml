import QtQuick;

Rectangle{
      id: rootrect;
      smooth: true; antialiasing: false;
      property real value: 0.0;
      property color loadedColor: "#00FF00";
      property bool enableColorSmoothing: false;
      color: "#000000";
      // anchors{
      // left: parent.right;
      // right: parent.right;
      // }
      gradient: Gradient{
      orientation: Gradient.Horizontal;
      GradientStop{color: rootrect.color; position: (rootrect.enableColorSmoothing)? 1.0 - rootrect.value:rootrect.value;}
      GradientStop{color: rootrect.loadedColor; position:rootrect.value;}
      }


}