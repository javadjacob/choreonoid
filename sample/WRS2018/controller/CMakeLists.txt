choreonoid_add_simple_controller(SpreaderController SpreaderController.cpp)
choreonoid_add_simple_controller(CarT3Controller CarT3Controller.cpp)
target_link_libraries(CarT3Controller SpreaderController)

if(BUILD_SCENE_EFFECTS_PLUGIN)
  choreonoid_add_simple_controller(FireController FireController.cpp)
  target_link_libraries(FireController CnoidSceneEffectsPlugin)
  choreonoid_add_simple_controller(HoseNozzleController HoseNozzleController.cpp)
  target_link_libraries(HoseNozzleController FireController)
endif()

choreonoid_add_simple_controller(RockDrillController RockDrillController.cpp)
choreonoid_add_simple_controller(BoaringTargetController BoaringTargetController.cpp)
target_link_libraries(BoaringTargetController RockDrillController)
