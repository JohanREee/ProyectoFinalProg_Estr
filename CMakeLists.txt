cmake_minimum_required(VERSION 3.0.0)
project(Prueba VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCE_FILES main.cpp inicio_sesion.cpp lote.cpp structs.h registros.cpp reporte_pdf.cpp producto.cpp movimientos.cpp menus.cpp lote.cpp complemento.cpp alertas.cpp archivos_texto.cpp usuario.cpp)
add_executable(Proyecto_Final ${SOURCE_FILES})

find_package(unofficial-libharu CONFIG REQUIRED)
target_link_libraries(Proyecto_Final PRIVATE unofficial::libharu::hpdf)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Proyecto_Final PRIVATE nlohmann_json::nlohmann_json)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
