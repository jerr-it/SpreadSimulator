
set(SOURCES
        MedicalComponent.c
        SimulatorStats.c
        SimulationSettings.c
        SpreadSimulator.c)

set(HEADERS
        MedicalComponent.h
        SimulatorStats.h
        SimulationSettings.h
        SpreadSimulator.h)

add_subdirectory(Quadtree)

add_library(SpreadSimulator SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SpreadSimulator Quadtree)
