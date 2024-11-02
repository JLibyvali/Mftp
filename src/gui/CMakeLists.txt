set(SRCS_FILES_GUI PARENT_SCOPE
    FileSystem/FileOptons.cpp
    FileSystem/FileSystem.cpp
    FileSystem/IODevice.cpp
    Person/person.cpp
    UI/UI_MWidgets.cpp
    UI/UI_Menus.cpp
    UI/MainWindow.cpp
    Action/TreeViewAction.cpp
    main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE . Action Exception FileSystem Person UI)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Core Qt6::Gui)