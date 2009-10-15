################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BaseObject.cpp \
../BitmapTexture.cpp \
../Camera.cpp \
../Engine.cpp \
../I3DObject.cpp \
../IGameplay.cpp \
../IKeyboard.cpp \
../IMaterial.cpp \
../IMouse.cpp \
../IRenderable.cpp \
../ITexture.cpp \
../IViewable.cpp \
../Main.cpp \
../Mesh.cpp \
../OBJ3DObject.cpp \
../StandardMaterial.cpp \
../SunRasterTexture.cpp \
../TestFrame.cpp 

OBJS += \
./BaseObject.o \
./BitmapTexture.o \
./Camera.o \
./Engine.o \
./I3DObject.o \
./IGameplay.o \
./IKeyboard.o \
./IMaterial.o \
./IMouse.o \
./IRenderable.o \
./ITexture.o \
./IViewable.o \
./Main.o \
./Mesh.o \
./OBJ3DObject.o \
./StandardMaterial.o \
./SunRasterTexture.o \
./TestFrame.o 

CPP_DEPS += \
./BaseObject.d \
./BitmapTexture.d \
./Camera.d \
./Engine.d \
./I3DObject.d \
./IGameplay.d \
./IKeyboard.d \
./IMaterial.d \
./IMouse.d \
./IRenderable.d \
./ITexture.d \
./IViewable.d \
./Main.d \
./Mesh.d \
./OBJ3DObject.d \
./StandardMaterial.d \
./SunRasterTexture.d \
./TestFrame.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


