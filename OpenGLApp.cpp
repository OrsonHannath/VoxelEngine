//
// Created by User on 23/03/2023.
//

#include "OpenGLApp.h"

// The constructor (default)
OpenGLApp::OpenGLApp() {

    isRunning = true;
}

bool OpenGLApp::OnInit() {

    // Initialise GLFW
    glewExperimental = true; // Needed for core profile
    if( !glfwInit() ) {

        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    // Create the OpenGL Window
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( wWidth, wHeight, "Tutorial 01", NULL, NULL);
    if( window == NULL ){

        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {

        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Create the Vertex Array Object (VAO)
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Set Z-Buffer on
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // Accept fragment if it closer to the camera than the former one

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Load in the shaders
    GLuint* programIDs = LoadShaders("../shaders/VertexShader.vertexshader", "../shaders/FragmentShader.fragmentshader", "../shaders/VoxelComputeShader.computeshader");

    programID = *(programIDs);
    computeProgramID = *(programIDs + 1);

    // Uniform Handles
    // Get a handle for our "MVP" uniform
    matrixID = glGetUniformLocation(programID, "MVP");

    // Create a new Scene Manager
    sceneManager = new SceneManager(&deltaTime);

    // Set all GLHandles to be passed into scene (These were not here originally and was causing programID's to not be set during scene init)
    std::map<std::string, GLuint> GLHandles;
    GLHandles["matrixID"]= matrixID;
    GLHandles["programID"] = programID;
    GLHandles["computeProgramID"] = computeProgramID;

    // Add a new scene to the scene manager
    Scene* scene = new TestingScene("Testing Scene", window, GLHandles);
    sceneManager->AddScene(scene);

    // Set the current scene
    sceneManager->SetCurrentScene(scene);

    return true;
}

int OpenGLApp::OnExecute(int width, int height) {

    wWidth = width;
    wHeight = height;

    // Initialize the app
    if(OnInit()){

        while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ){

            OnLoop();
            OnRender();
        }
    }

    return 0;
}

void OpenGLApp::OnLoop() {

    // Time Management
    double currentTime = glfwGetTime();
    deltaTime = DeltaTime(time_);
    time_ = currentTime;
    std::string fpsStr = std::to_string((int)(1.0/deltaTime)) + "fps";
    glfwSetWindowTitle(window, ("VoxelEngine " + fpsStr).c_str());

}

void OpenGLApp::OnRender() {

    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the current scene
    sceneManager->RenderScene(sceneManager->GetCurrentScene());

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void OpenGLApp::OnExit() {

    // Exit the App Here
}

GLuint* OpenGLApp::LoadShaders(const char *vertex_file_path, const char *fragment_file_path, const char *compute_file_path) {

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint ComputeShaderID = glCreateShader(GL_COMPUTE_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    // Read the Compute Shader code from the file
    std::string ComputeShaderCode;
    std::ifstream ComputeShaderStream(compute_file_path, std::ios::in);
    if(ComputeShaderStream.is_open()){
        std::stringstream sstr;
        sstr << ComputeShaderStream.rdbuf();
        ComputeShaderCode = sstr.str();
        ComputeShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Compile Compute Shader
    printf("Compiling shader : %s\n", compute_file_path);
    char const * ComputeSourcePointer = ComputeShaderCode.c_str();
    glShaderSource(ComputeShaderID, 1, &ComputeSourcePointer , NULL);
    glCompileShader(ComputeShaderID);

    // Check Compute Shader
    glGetShaderiv(ComputeShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(ComputeShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ComputeShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(ComputeShaderID, InfoLogLength, NULL, &ComputeShaderErrorMessage[0]);
        printf("%s\n", &ComputeShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking main program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Link the compute program
    printf("Linking compute program\n");
    GLuint ComputeProgramID = glCreateProgram();
    glAttachShader(ComputeProgramID, ComputeShaderID);
    glCompileShader(ComputeProgramID);
    glLinkProgram(ComputeProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    // Check the program
    glGetProgramiv(ComputeProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ComputeProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ComputeProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    glDeleteShader(ComputeShaderID);

    GLuint* programIDs = new GLuint[]{ProgramID, ComputeProgramID};
    return programIDs;
}