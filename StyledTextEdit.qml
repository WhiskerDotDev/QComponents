import QtQuick;

Rectangle{
      id: root;
      smooth: false; antialiasing: false;
      border.pixelAligned: true;
      clip: true;
      // active/inactive colors
      property point size;
      property point i_size;
      property point position; property alias pos: root.position;
      width: size.x; height: size.y;
      implicitWidth: i_size.x; implicitHeight: i_size.y;
      x: position.x; y: position.y; z: parent.z + 1;

      // Visual properties
      property color activeAccentColor: "blue";
      property color defaultAccentColor: "black";
      property Component cursorComponent;
      border.width: 2;
      signal editingFinished();

TextInput{
            id: m_content;
            z: root.z + 1; // rework
            // width: root.width - (root.border.width * 2); height: root.height - (root.border.width * 2);
            // x: root.border.width; y: root.border.width;
            anchors.fill: root;
            anchors.margins: root.border.width;
            clip: root.clip; enabled: true;
            smooth: root.smooth; antialiasing: root.antialiasing;
            renderType: TextEdit.NativeRendering;
            cursorDelegate: root.cursorComponent;
            Keys.onReturnPressed: function(){if(this.activeFocus === true)root.editingFinished();this.focus = false;}
            wrapMode: TextEdit.NoWrap;
            onActiveFocusChanged: function(){ root.border.color = (m_content.activeFocus === true)? root.activeAccentColor : root.defaultAccentColor; }
      }property alias content: m_content;

      // aliases:
      property alias readOnly: m_content.readOnly;
      property alias text: m_content.text;
      property alias padding: m_content.padding;
      property alias textcolor: m_content.color;
      property alias italic: m_content.font.italic;
      property alias bold: m_content.font.bold;
      property alias fontfamily: m_content.font.family;
      property alias fontPixelSize: m_content.font.pixelSize;
      property alias cursorPosition: m_content.cursorPosition;
      property alias wrapMode: m_content.wrapMode;
      property alias cursorVisible: m_content.cursorVisible;
      property alias renderType: m_content.renderType;
}