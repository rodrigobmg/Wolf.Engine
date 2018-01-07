#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/644c5920/imgui.o \
	${OBJECTDIR}/_ext/644c5920/imgui_demo.o \
	${OBJECTDIR}/_ext/644c5920/imgui_draw.o \
	${OBJECTDIR}/_ext/1fb97ba1/CullingThreadpool.o \
	${OBJECTDIR}/_ext/1fb97ba1/FrameRecorder.o \
	${OBJECTDIR}/_ext/1fb97ba1/MaskedOcclusionCulling.o \
	${OBJECTDIR}/_ext/1fb97ba1/MaskedOcclusionCullingAVX2.o \
	${OBJECTDIR}/_ext/1fb97ba1/MaskedOcclusionCullingAVX512.o \
	${OBJECTDIR}/_ext/b7d810ff/w_bounding_frustum.o \
	${OBJECTDIR}/_ext/b7d810ff/w_game.o \
	${OBJECTDIR}/_ext/1b66276a/w_buffer.o \
	${OBJECTDIR}/_ext/1b66276a/w_command_buffer.o \
	${OBJECTDIR}/_ext/1b66276a/w_fences.o \
	${OBJECTDIR}/_ext/1b66276a/w_frame_buffer.o \
	${OBJECTDIR}/_ext/1b66276a/w_imgui.o \
	${OBJECTDIR}/_ext/1b66276a/w_mesh.o \
	${OBJECTDIR}/_ext/1b66276a/w_pipeline.o \
	${OBJECTDIR}/_ext/1b66276a/w_queue.o \
	${OBJECTDIR}/_ext/1b66276a/w_render_pass.o \
	${OBJECTDIR}/_ext/1b66276a/w_render_target.o \
	${OBJECTDIR}/_ext/1b66276a/w_semaphore.o \
	${OBJECTDIR}/_ext/1b66276a/w_shader.o \
	${OBJECTDIR}/_ext/1b66276a/w_texture.o \
	${OBJECTDIR}/_ext/24207458/w_graphics_device_manager.o \
	${OBJECTDIR}/_ext/24207458/w_render_pch.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../../../../VulkanSDK/1.0.65.0/x86_64/lib -L../../../dependencies/tbb/oss/linux/lib/intel64/gcc4.7 -L../../../dependencies/msgpack/lib/linux/x64/debug -lxcb -lmsgpackc -lvulkan

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/../../../../../bin/x64/${CND_CONF}/${CND_PLATFORM}/libwolf.vulkan.${CND_DLIB_EXT}

${CND_DISTDIR}/../../../../../bin/x64/${CND_CONF}/${CND_PLATFORM}/libwolf.vulkan.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/../../../../../bin/x64/${CND_CONF}/${CND_PLATFORM}
	clang++ -o ${CND_DISTDIR}/../../../../../bin/x64/${CND_CONF}/${CND_PLATFORM}/libwolf.vulkan.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/_ext/644c5920/imgui.o: ../../../src/wolf.render/imgui/imgui.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/644c5920
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/644c5920/imgui.o ../../../src/wolf.render/imgui/imgui.cpp

${OBJECTDIR}/_ext/644c5920/imgui_demo.o: ../../../src/wolf.render/imgui/imgui_demo.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/644c5920
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/644c5920/imgui_demo.o ../../../src/wolf.render/imgui/imgui_demo.cpp

${OBJECTDIR}/_ext/644c5920/imgui_draw.o: ../../../src/wolf.render/imgui/imgui_draw.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/644c5920
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/644c5920/imgui_draw.o ../../../src/wolf.render/imgui/imgui_draw.cpp

${OBJECTDIR}/_ext/1fb97ba1/CullingThreadpool.o: ../../../src/wolf.render/masked_occlusion_culling/CullingThreadpool.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1fb97ba1
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1fb97ba1/CullingThreadpool.o ../../../src/wolf.render/masked_occlusion_culling/CullingThreadpool.cpp

${OBJECTDIR}/_ext/1fb97ba1/FrameRecorder.o: ../../../src/wolf.render/masked_occlusion_culling/FrameRecorder.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1fb97ba1
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1fb97ba1/FrameRecorder.o ../../../src/wolf.render/masked_occlusion_culling/FrameRecorder.cpp

${OBJECTDIR}/_ext/1fb97ba1/MaskedOcclusionCulling.o: ../../../src/wolf.render/masked_occlusion_culling/MaskedOcclusionCulling.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1fb97ba1
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -msse4.2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1fb97ba1/MaskedOcclusionCulling.o ../../../src/wolf.render/masked_occlusion_culling/MaskedOcclusionCulling.cpp

${OBJECTDIR}/_ext/1fb97ba1/MaskedOcclusionCullingAVX2.o: ../../../src/wolf.render/masked_occlusion_culling/MaskedOcclusionCullingAVX2.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1fb97ba1
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -mavx2 -mfma -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1fb97ba1/MaskedOcclusionCullingAVX2.o ../../../src/wolf.render/masked_occlusion_culling/MaskedOcclusionCullingAVX2.cpp

${OBJECTDIR}/_ext/1fb97ba1/MaskedOcclusionCullingAVX512.o: ../../../src/wolf.render/masked_occlusion_culling/MaskedOcclusionCullingAVX512.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1fb97ba1
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -march=skylake-avx512 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1fb97ba1/MaskedOcclusionCullingAVX512.o ../../../src/wolf.render/masked_occlusion_culling/MaskedOcclusionCullingAVX512.cpp

${OBJECTDIR}/_ext/b7d810ff/w_bounding_frustum.o: ../../../src/wolf.render/w_framework/w_bounding_frustum.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b7d810ff
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7d810ff/w_bounding_frustum.o ../../../src/wolf.render/w_framework/w_bounding_frustum.cpp

${OBJECTDIR}/_ext/b7d810ff/w_game.o: ../../../src/wolf.render/w_framework/w_game.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b7d810ff
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7d810ff/w_game.o ../../../src/wolf.render/w_framework/w_game.cpp

${OBJECTDIR}/_ext/1b66276a/w_buffer.o: ../../../src/wolf.render/w_graphics/w_buffer.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_buffer.o ../../../src/wolf.render/w_graphics/w_buffer.cpp

${OBJECTDIR}/_ext/1b66276a/w_command_buffer.o: ../../../src/wolf.render/w_graphics/w_command_buffer.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_command_buffer.o ../../../src/wolf.render/w_graphics/w_command_buffer.cpp

${OBJECTDIR}/_ext/1b66276a/w_fences.o: ../../../src/wolf.render/w_graphics/w_fences.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_fences.o ../../../src/wolf.render/w_graphics/w_fences.cpp

${OBJECTDIR}/_ext/1b66276a/w_frame_buffer.o: ../../../src/wolf.render/w_graphics/w_frame_buffer.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_frame_buffer.o ../../../src/wolf.render/w_graphics/w_frame_buffer.cpp

${OBJECTDIR}/_ext/1b66276a/w_imgui.o: ../../../src/wolf.render/w_graphics/w_imgui.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_imgui.o ../../../src/wolf.render/w_graphics/w_imgui.cpp

${OBJECTDIR}/_ext/1b66276a/w_mesh.o: ../../../src/wolf.render/w_graphics/w_mesh.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_mesh.o ../../../src/wolf.render/w_graphics/w_mesh.cpp

${OBJECTDIR}/_ext/1b66276a/w_pipeline.o: ../../../src/wolf.render/w_graphics/w_pipeline.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_pipeline.o ../../../src/wolf.render/w_graphics/w_pipeline.cpp

${OBJECTDIR}/_ext/1b66276a/w_queue.o: ../../../src/wolf.render/w_graphics/w_queue.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_queue.o ../../../src/wolf.render/w_graphics/w_queue.cpp

${OBJECTDIR}/_ext/1b66276a/w_render_pass.o: ../../../src/wolf.render/w_graphics/w_render_pass.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_render_pass.o ../../../src/wolf.render/w_graphics/w_render_pass.cpp

${OBJECTDIR}/_ext/1b66276a/w_render_target.o: ../../../src/wolf.render/w_graphics/w_render_target.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_render_target.o ../../../src/wolf.render/w_graphics/w_render_target.cpp

${OBJECTDIR}/_ext/1b66276a/w_semaphore.o: ../../../src/wolf.render/w_graphics/w_semaphore.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_semaphore.o ../../../src/wolf.render/w_graphics/w_semaphore.cpp

${OBJECTDIR}/_ext/1b66276a/w_shader.o: ../../../src/wolf.render/w_graphics/w_shader.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_shader.o ../../../src/wolf.render/w_graphics/w_shader.cpp

${OBJECTDIR}/_ext/1b66276a/w_texture.o: ../../../src/wolf.render/w_graphics/w_texture.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/1b66276a
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1b66276a/w_texture.o ../../../src/wolf.render/w_graphics/w_texture.cpp

${OBJECTDIR}/_ext/24207458/w_graphics_device_manager.o: ../../../src/wolf.render/w_graphics_device_manager.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/24207458
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24207458/w_graphics_device_manager.o ../../../src/wolf.render/w_graphics_device_manager.cpp

${OBJECTDIR}/_ext/24207458/w_render_pch.o: ../../../src/wolf.render/w_render_pch.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/24207458
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGLM_FORCE_DEPTH_ZERO_TO_ONE -D_DEBUG -D__VULKAN__ -D__WOLF_RENDER__ -I../../../src/wolf.system -I../../../src/wolf.render -I../../../src/wolf.content_pipeline -I../../../dependencies/tbb/oss/linux/include -I../../../dependencies/msgpack/include -I../../../../../../VulkanSDK/1.0.65.0/x86_64/include -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24207458/w_render_pch.o ../../../src/wolf.render/w_render_pch.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
