
#include "glad.h"

#include "GLFW/glfw3.h"
#include "image.h"
#include "math.h"
#include "math/mat4.h"
#include "math/vector.h"
#include "stdio.h"
#include "vertex.h"

int key_pressed[GLFW_KEY_LAST] = {0};
float zMove = 0.0;
float zMinus = 0.0;
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, int key, int scancode, int action,
                  int mods);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return -1;
  }

  // build and compile our shader zprogram
  // ------------------------------------

  char filepath[10] = "";
  Vertex vertex = createVertex(filepath);
  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
 float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // load and create a texture
  // -------------------------
  Image image;
  loadImage("resources/container.jpg",&image);
  mat4f translate = {0};
 mat4f scaleM = {0};
 mat4f rotateM = {0};
 mat4f temp = {0};
 mat4f projection = {0};
  createProjection(90.f,&projection);
  mat4(1.0f, &translate);
  mat4(1.0f, &scaleM);
mat4(1.0f, &rotateM);
  vector translateVector = {x : 0.1f, y : 0.1f, z : 0.0f};

  vector rotationVector = {x: 1.0f,y:1.0f, z:1.0f};

  float angle = 45;
  setUniformMatrix4f("translate", vertex.id, translate);
  setUniformMatrix4f("projection",vertex.id, projection);
  float previousTime = glfwGetTime();
  float currentTime = 0;
  int toMultiply = 0;
  glEnable(GL_DEPTH_TEST);
  mat4f res = {};
  glCullFace(GL_BACK);
  identity(&res);
  glfwSetKeyCallback(window, processInput);
  printMatix(projection);
  while (!glfwWindowShouldClose(window)) {

    float dt =1.0/60.f;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float scaleSpeed = 0.5f; // Adjust speed of scaling
    if (angle > 360.0f)
    {
      angle = 45.f;
    }
    angle = 45.f * glfwGetTime();

    // setTranslation(translateVector,&translate);
     translateVector.z = 1.f+zMove;
    //translateVector.y = zMove+0.2;
    vector sc = {x:1.f,y:1.f,z:1.f};
  
    setScale(sc,&scaleM); 
    setRotationX(rotationVector,angle,rotateM);
    setTranslation(translateVector,translate);
    transform(res,translate,rotateM,scaleM);
  
printf("-------------------\n");
  printMatix(res);  
 
printf("-------------------\n");
    setUniformMatrix4f("translate", vertex.id, res);
    
    glBindTexture(GL_TEXTURE_2D,image.id );
    glUseProgram(vertex.id);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,36 );

    glfwSwapBuffers(window);
    glfwPollEvents();
    previousTime = currentTime;
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
 glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, 1);
  }
  if (action == GLFW_PRESS && key == GLFW_KEY_KP_ADD && !key_pressed[key]) {
    zMove += 0.5;
    key_pressed[key] = 1;
  }
  if (action == GLFW_PRESS && key == GLFW_KEY_KP_SUBTRACT &&
      !key_pressed[key]) {
    zMove -= 0.5;
  } else if (GLFW_RELEASE == action) {
    key_pressed[key] = 0;
  }
  if(action == GLFW_REPEAT && key == GLFW_KEY_RIGHT){
    zMove += 0.1;
  }
if(action == GLFW_REPEAT && key == GLFW_KEY_LEFT){
    zMove -= 0.1;
  }
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}