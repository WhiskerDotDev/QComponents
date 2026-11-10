import QtQuick;

Image{
      id: rootimg;
      property point size;
      property point position;
      property alias pos: rootimg.position;
      enabled: true;
      smooth: false; antialiasing: false;
      property alias src: rootimg.source;

      width: size.x; height: size.y;
      x: position.x; y: position.y;
      z: parent.z + 1; // For the sake of TapHandler working in presence of MouseArea

      TapHandler{
            id: m_hitbox;
            target: rootimg; enabled: rootimg.enabled
            acceptedButtons: Qt.LeftButton;
            gesturePolicy: TapHandler.ReleaseWithinBounds; //TODO: in other files, add a "scenePosition" value, for those with a TapHandler
      } property alias hitbox: m_hitbox;

}