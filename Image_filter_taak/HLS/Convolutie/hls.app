<project xmlns="com.autoesl.autopilot.project" name="Convolutie" top="applyConvolution" projectType="C/C++">
    <includePaths/>
    <libraryPaths/>
    <Simulation argv="input.png">
        <SimFlow name="csim" ldflags="" csimMode="2" lastCsimMode="2"/>
    </Simulation>
    <files xmlns="">
        <file name="Convolutie/source/Convolutie.c" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="Convolutie/source/Convolutie.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="Convolutie/source/stb_image.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="Convolutie/source/stb_image_write.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="../source/Convolutie.h" sc="0" tb="1" cflags="-Wno-unknown-pragmas" csimflags="" blackbox="false"/>
        <file name="../source/Convolutie_TB.c" sc="0" tb="1" cflags="-Wno-unknown-pragmas" csimflags="" blackbox="false"/>
        <file name="../source/input.png" sc="0" tb="1" cflags="-Wno-unknown-pragmas" csimflags="" blackbox="false"/>
        <file name="../source/stb_image.h" sc="0" tb="1" cflags="-Wno-unknown-pragmas" csimflags="" blackbox="false"/>
        <file name="../source/stb_image_write.h" sc="0" tb="1" cflags="-Wno-unknown-pragmas" csimflags="" blackbox="false"/>
    </files>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

