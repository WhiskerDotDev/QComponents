import QtQuick;
import QComponents;

Rectangle{
      id: rootrect;
      smooth: false; antialiasing: false;
      clip: false;
      z: parent.z + 1;
      property point size;
      property point i_size;
      property point position;
      property alias pos: rootrect.position;
      enabled: true;

      QtObject{
            id: __vars;
            property string unitstr : "x";
            property real currentVal: 0.0;
            property string finalVal: rootrect.currentvalue + __vars.unitstr;
      }

      property int textWidth: Math.round(rootrect.width * 0.8);

      property bool haveMinMaxLimits: false;
      property Component cursorComponent;
      property bool reboundOnOverflow: true;
      property bool resetOnRightClick: true;
      property real max : 10.0; property real min : -1.0;
      property int decimalPlaces: 3;
      property real defaultValue: 0.0;
      readonly property real currentvalue : roundToDecimalPlace( __vars.currentVal, rootrect.decimalPlaces );
      readonly property alias currentFloatVal: __vars.currentVal;
      property real stepping : 0.05;
      readonly property int int_roundedvalue : __vars.currentVal > 1.0? Math.round(__vars.currentVal) : null;

      function roundToDecimalPlace(num : real, places : int, stepping = rootrect.stepping) : real{
            if( ((num >= (-( rootrect.stepping ) +  (rootrect.stepping / 10) ) )&&( num <= (rootrect.stepping -  (rootrect.stepping / 10) )  ) ) ){ return 0.0;}else{
                  return Number(num.toPrecision( places +1  ));  }
      }

      function increment(steps = 1) : void{
            __vars.currentVal += (steps * rootrect.stepping );
            if( (__vars.currentVal >= rootrect.max) && rootrect.haveMinMaxLimits === true){ __vars.currentVal = rootrect.max; }else if(( rootrect.currentvalue  > rootrect.max) && rootrect.reboundOnOverflow === true){__vars.currentVal = rootrect.min;}
      }

      function decrement(steps = 1) : void{
            __vars.currentVal -= (steps * rootrect.stepping );
            if (( __vars.currentVal <= rootrect.min) && rootrect.haveMinMaxLimits === true){__vars.currentVal = rootrect.min;}else if((  rootrect.currentvalue < rootrect.min) && rootrect.reboundOnOverflow === true){__vars.currentVal = rootrect.max;}
      }

      function setValue(val : real) : void{
            if(val >= rootrect.max){ val = rootrect.max; }
            else if(val <= rootrect.min){ val = rootrect.min; }
            else{ __vars.currentVal = val; }
      }

      function setValue_STR(val : string) : void{
            let val_f = parseFloat(val.replace(__vars.unitstr, ""));
            if(val_f >= rootrect.max){ val_f = rootrect.max; }
            else if(val_f <= rootrect.min){ val_f = rootrect.min; }
            else{ __vars.currentVal = val_f; }
      }



      function setUnit(unitstring : string) : void{
            if(unitstring.length > 3){ __vars.unitstr = unitstring.slice(0, 3); }
            else{__vars.unitstr = unitstring;}
      }

      //SCROLL HANDLER:

      SimpleScrollHandler{
            target: rootrect;
            onWheelUp:()=>{rootrect.increment();rootrect.forceActiveFocus();}
            onWheelDown:()=>{rootrect.decrement();rootrect.forceActiveFocus();}
      }

      // TAP HANDLER:

      TapHandler{
            target:rootrect;
            acceptedButtons: Qt.RightButton;
            onTapped:__vars.currentVal = rootrect.defaultValue;
      }

      //  VISUAL COMPONENTS:

      Item{
            id: m_arrowColumn
            parent: rootrect;
            visible: true;
            smooth: rootrect.smooth; antialiasing: rootrect.antialiasing;
            width: rootrect.width - rootrect.textWidth;
            // height: rootrect.height - (rootrect.border.width * 2);
            // x: rootrect.textWidth -  rootrect.border.width; y: rootrect.border.width; z: rootrect.z;
            anchors{
                  right: rootrect.right;
                  top: rootrect.top;
                  bottom: rootrect.bottom;
            }

            property real spacing: Math.round(this.width) % 2 === 0? 0 : 1; // what's a pixel of spacing?
            property int availableHeight: m_arrowColumn.height - ((m_arrowColumn.height - m_arrowColumn.spacing) / 2);

            ClickableIcon{
                  id: m_upArrow;
                  // y: parent.y; z: rootrect.z;
                  // width: parent.width;
                  // height: parent.availableHeight;
                  anchors{
                        fill: m_arrowColumn;
                        bottomMargin: m_arrowColumn.availableHeight;
                  }
                  hitbox.onTapped:()=>{rootrect.increment(); rootrect.forceActiveFocus();}
            }

            ClickableIcon{
                  id: m_downArrow;
                  // y: parent.availableHeight + 1;
                  // z: rootrect.z;
                  // width: parent.width;
                  // height: parent.availableHeight;
                  anchors{
                        fill: m_arrowColumn;
                        topMargin: m_arrowColumn.availableHeight;
                  }
                  hitbox.onTapped:()=>{rootrect.decrement(); rootrect.forceActiveFocus();}
            }

      }property alias arrowColumn : m_arrowColumn;

      property alias upArrow: m_upArrow;
      property alias downArrow: m_downArrow;

      TextEdit{
            id: __content;
            // width: rootrect.textWidth;height: rootrect.height - (rootrect.border.width * 2);
            // x: rootrect.border.width; y: rootrect.border.width; z: rootrect.z;
            anchors{
                  right:m_arrowColumn.left;
                  left: rootrect.left;
                  top: rootrect.top;
                  bottom: rootrect.bottom;
            }
            clip: true; enabled: true;
            smooth: rootrect.smooth; antialiasing: rootrect.antialiasing;
            renderType: TextEdit.NativeRendering;
            textFormat: TextEdit.PlainText
            cursorDelegate: rootrect.cursorComponent;
            Keys.onReturnPressed: function(){if(this.activeFocus === true){this.focus = false; rootrect.focus = false; rootrect.setValue_STR(this.text)}}
            wrapMode: TextEdit.NoWrap;
            text: __vars.finalVal;
      } property alias textBox: __content;


      property alias readOnly: __content.readOnly;
      property alias text: __content.text;
      property alias padding: __content.padding;
      property alias textcolor: __content.color;
      property alias italic: __content.font.italic;
      property alias bold: __content.font.bold;
      property alias fontfamily: __content.font.family;
      property alias fontPixelSize: __content.font.pixelSize;
      property alias cursorPosition: __content.cursorPosition;
      property alias wrapMode: __content.wrapMode;
      property alias cursorVisible: __content.cursorVisible;
      property alias renderType: __content.renderType;


      Keys.onUpPressed: ()=>{rootrect.increment(); rootrect.forceActiveFocus();}
      Keys.onDownPressed: ()=>{rootrect.decrement(); rootrect.forceActiveFocus();}

}
