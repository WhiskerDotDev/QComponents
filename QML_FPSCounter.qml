import QtQuick;
// a QML/JS-only FPS counter... I have a C++ implementation which is more efficient and functional.

Timer{
      id: root_tmr
      interval: 1000;
      repeat: true;
      triggeredOnStart: false;

      required property Window win;
      property int currentFrameCount;
      property int frameCount;
      property bool logFramerateToConsole: true;

      property Connections connection: Connections{
            target: root_tmr.win;
            function onFrameSwapped(){ root_tmr.currentFrameCount +=1;}
      }

      function outputResult() : void{
            console.log("FPS: " + root_tmr.frameCount);
      }

      onTriggered: ()=>{
                         root_tmr.frameCount = Math.round( root_tmr.currentFrameCount / (root_tmr.interval / 1000) );
                         if(root_tmr.logFramerateToConsole === true){ outputResult(); }
                         root_tmr.currentFrameCount = 0;
                   }
}