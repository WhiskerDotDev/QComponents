import QtQuick;

Rectangle{
      id: root;
      clip: root.radius > 0;

      property point size;
      property point i_size;
      property point position;
      property alias pos: root.position;
      // enabled: true;
      smooth: false; antialiasing: false;
      border.pixelAligned: true;

      width: size.x; height: size.y;
      implicitWidth: i_size.x; implicitHeight: i_size.y;
      x: position.x; y: position.y;
      z: parent.z + 1;

      TapHandler{
            id: m_hitbox;
            target: root; enabled: root.enabled
            acceptedButtons: Qt.LeftButton;
            gesturePolicy: TapHandler.ReleaseWithinBounds;
      } property alias hitbox: m_hitbox;
      // Corresponding handlers:
      //(hitbox.) onSingleTapped, onDoubleTapped, etc.
}
