import QtQuick

MouseArea {
      id: root;
      required property Window win;
      anchors.fill: parent;
      // smooth: false; antialiasing: false;
      hoverEnabled: true;
      propagateComposedEvents: true;
      property int verticalBounds;
      property int horizontalBounds;
      enabled: (win.visibility == Window.FullScreen || win.visibility === Window.Maximized) ? false : true; //Disables resize edges if window is fullscreen or maximized.
      QtObject {
            id: internal_vals;
            property int segment: 5;
      }
      onWidthChanged: internal_vals.segment = 5;
      onHeightChanged: internal_vals.segment = 5;

      /*
    The window is split into 9 segments:
    1 | 2 | 3
    +-+-+-+
    4 | 5 | 6
    +-+-+-+
    7 | 8 | 9
    */

      function updateSegment(mouseX, mouseY) {
            // Evaluate our position relative to the bounds once
            let isLeft = (mouseX <= root.horizontalBounds);
            let isRight = (mouseX >= root.width - root.horizontalBounds);
            let isTop = (mouseY <= root.verticalBounds);
            let isBottom = (mouseY >= root.height - root.verticalBounds);

            if (isTop && isLeft) { internal_vals.segment = 1; }
            else if (isTop && isRight)   { internal_vals.segment = 3; }
            else if (isTop) { internal_vals.segment = 2; }
            else if (isBottom && isLeft) { internal_vals.segment = 7; }
            else if (isBottom && isRight){ internal_vals.segment = 9; }
            else if (isBottom) { internal_vals.segment = 8; }
            else if (isLeft) { internal_vals.segment = 4; }
            else if (isRight) { internal_vals.segment = 6; }
             else { internal_vals.segment = 5; } // Center
      }

      onPositionChanged: (mouse) => {
                               updateSegment(mouse.x, mouse.y);

                               switch(internal_vals.segment) {
                                     case 5: cursorShape = Qt.ArrowCursor; break;

                                     case 2:
                                     case 8: cursorShape = Qt.SizeVerCursor; break;

                                     case 4:
                                     case 6: cursorShape = Qt.SizeHorCursor; break;

                                     case 3:
                                     case 7: cursorShape = Qt.SizeBDiagCursor; break;

                                     case 1:
                                     case 9: cursorShape = Qt.SizeFDiagCursor; break;
                               }
                         }

      onPressed: (mouse) => {
                       // IF WE ARE IN THE CENTER (5), IGNORE THE CLICK AND PASS IT DOWN
                       if (internal_vals.segment === 5) {
                             mouse.accepted = false;
                             return;
                       }
                       switch(internal_vals.segment) {
                             case 1: win.startSystemResize(Qt.TopEdge | Qt.LeftEdge); break;
                             case 2: win.startSystemResize(Qt.TopEdge); break;
                             case 3: win.startSystemResize(Qt.TopEdge | Qt.RightEdge); break;
                             case 4: win.startSystemResize(Qt.LeftEdge); break;
                             case 6: win.startSystemResize(Qt.RightEdge); break;
                             case 7: win.startSystemResize(Qt.BottomEdge | Qt.LeftEdge); break;
                             case 8: win.startSystemResize(Qt.BottomEdge); break;
                             case 9: win.startSystemResize(Qt.BottomEdge | Qt.RightEdge); break;
                       }
                 }
}