cmake_minimum_required(VERSION 3.16)
project(QComponentsproj VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    add_compile_options(/Ox /GF)
    add_compile_options(/MT)
endif()

find_package(Qt6 REQUIRED COMPONENTS

    Qml QmlPrivate
    Quick QuickPrivate
    Gui  GuiPrivate
    # Multimedia
)

qt_add_qml_module(QComponentsproj
    URI "QComponents"
    VERSION 1.0
    QML_FILES
    BasicButton.qml
    IconButton.qml
    ResizeEdges.qml
    DefaultWindowControls.qml
    TitleBar.qml
    TextButton.qml
    SimpleBorderImage.qml
    StyledTextEdit.qml
    SimpleSpinBox.qml
    ClickableIcon.qml
    SimpleScrollHandler.qml
    LabelledSpinBox.qml
    SimpleProgressBar.qml
    LabelledIcon.qml

    SOURCES
    FPSCOUNTER.hpp
    ImageSource.hpp
    CpuRenderedImage.hpp
    GpuRenderedImage.hpp
    ImageNode.hpp

    DEPENDENCIES
    QtQuick
    QtQml
    QtGui
    QtCore
    # QtMultiMedia

    NO_GENERATE_AOT_VALIDATION
    ENABLE_TYPE_COMPILER
    STATIC

)

target_link_libraries(QComponentsproj PRIVATE Qt6::Qml Qt6::Quick Qt6::QuickPrivate Qt6::QmlPrivate

Qt6::Core
Qt6::Gui
Qt6::GuiPrivate
Qt6::Multimedia
)

