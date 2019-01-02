rcf_generate(executable RF_CONSOLE_SMOKETEST ConsoleSmokeTest "Tests/IO" "tests/ConsoleSmokeTest.cpp")
    rcf_dependencies(RadonFramework RadonFrameworkConsole)
rcf_endgenerate()

rcf_generate(executable RF_CONSOLE_PARAMETERTEST ParameterTest "Tests/IO" "tests/ParameterTest.cpp")
    rcf_dependencies(RadonFramework RadonFrameworkConsole)
rcf_endgenerate()