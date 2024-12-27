#include <iostream>
#include "Menu.h"
#include "LightManager.h"
#include "TempManager.h"
#include "SpeakerManager.h"
#include "RadiatorManager.h" // includes all device type managers //
#include "ThermostatManager.h"

using namespace std;

int main()
{
    Menu menu;
    menu.run(); // Starts the menu //

    return 0; 
}

// For loading my collection of smart devices I have chosen to use text file I/O //
// This inlines with the briefs instructions of loading a classes smart devices from a single file //
// Websites used in research for thid will be listed in the comment block below //

// LIST OF LINKS TO ALL WEBSITES USED TO HELP IN THIS PROJECT //
// https://www.tutorialspoint.com/c_standard_library/index.htm //
// This helps to understand the C++ library and STL //
// https://en.cppreference.com/w/ //
// This I used to touch up my knowledge on various C++ concepts //
// Websites used for File I/O research: //
// https://cplusplus.com/doc/tutorial/files/ //
// https://www.programiz.com/cpp-programming/file-handling //
// https://www.w3schools.com/cpp/cpp_files.asp //
// https://www.studytonight.com/cpp/file-streams-in-cpp.php //
// (for file handling and stream logic) //
// https://www.geeksforgeeks.org/serialize-and-deserialize-an-object-in-cpp/ //
// https://cplusplus.com/doc/tutorial/basic_io/ //
// helped me learn about input and ouptut streams //
// https://www.geeksforgeeks.org/header-guard-in-c/?ref=gcse_outind //
// This was used to learn about header file guards, as they prevent multiple definition and reduce compilation time //
// I also chose to used std:: explicity as opposed to using namespace std //
// This is because it avoids namespace collisions and enhances the clarity and readability of the code //
// https://www.tutorialspoint.com/cplusplus/cpp_omitting_namespace.htm //
// https://stackoverflow.com/questions/1452721/whats-the-problem-with-using-namespace-std (these 2 sites helped me understand this concept) //

// The CRUD and quick view functions are implemented in very similar ways throughout all device types //
// Therefore most comments have just been applied to the light class as it avoids redudancy by copying the same comments several times //
// However where changes or deviations occur, these will be commeneted upon //
