#-------------------------------------------------
#
# Project created by QtCreator 2013-02-05T19:20:22
#
#-------------------------------------------------

TARGET = famitracker
TEMPLATE = lib

TOP = ../..

DEFINES += FAMITRACKER_LIBRARY

DEFINES -= UNICODE

QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder -Wno-unused

INCLUDEPATH += \
   $$TOP/common

win32 {
	DEPENDENCYPATH = $$TOP/deps/Windows
}
mac {
	DEPENDENCYPATH = $$TOP/deps/osx
}
#unix:mac {
#	DEPENDENCYPATH = $$TOP/deps/linux
#}

win32 {

   SDL_CXXFLAGS = -I$$DEPENDENCYPATH/SDL
   SDL_LIBS =  -L$$DEPENDENCYPATH/SDL/ -lsdl
}

mac {

    isEmpty (SDL_CXXFLAGS) {
       SDL_CXXFLAGS = $$system(sdl-config --cflags)
    }

    SDL_CXXFLAGS += -I/usr/local/include/wine/windows/ -DUSE_WS_PREFIX -DWINE_UNICODE_NATIVE
    SDL_CFLAGS += -I/usr/local/include/wine/windows/

    isEmpty (SDL_LIBS) {
            SDL_LIBS = $$system(sdl-config --libs)
    }


}

unix:!mac {
    isEmpty (SDL_CXXFLAGS) {
       SDL_CXXFLAGS = $$system(sdl-config --cflags)
    }

    SDL_CXXFLAGS += -I/usr/include/wine/windows/ -DUSE_WS_PREFIX -DWINE_UNICODE_NATIVE -Dms_abi
    SDL_CFLAGS += -I/usr/include/wine/windows/

    isEmpty (SDL_LIBS) {
            SDL_LIBS = $$system(sdl-config --libs)
    }

   PREFIX = $$(PREFIX)
   isEmpty (PREFIX) {
      PREFIX = /usr/local
   }

   isEmpty (BINDIR) {
                BINDIR=$$PREFIX/bin
   }

   target.path = $$BINDIR
   INSTALLS += target
}

QMAKE_CXXFLAGS += $$SDL_CXXFLAGS
QMAKE_CFLAGS += $$SDL_CFLAGS
LIBS += $$SDL_LIBS

SOURCES += \
    TrackerChannel.cpp \
    SoundGen.cpp \
    Settings.cpp \
    Sequence.cpp \
    PatternEditor.cpp \
    PatternData.cpp \
    PatternCompiler.cpp \
    PatternAction.cpp \
    MainFrm.cpp \
    InstrumentVRC7.cpp \
    InstrumentVRC6.cpp \
    InstrumentS5B.cpp \
    InstrumentFDS.cpp \
    Instrument2A03.cpp \
    Instrument.cpp \
    Graphics.cpp \ 
    FrameEditor.cpp \
    FrameAction.cpp \
    FamiTrackerDoc.cpp \
    DocumentFile.cpp \
    ChannelsVRC7.cpp \
    ChannelsVRC6.cpp \
    ChannelsS5B.cpp \
    ChannelsN163.cpp \
    ChannelsMMC5.cpp \
    ChannelsFDS.cpp \
    Channels2A03.cpp \
    ChannelMap.cpp \
    ChannelHandler.cpp \
    Action.cpp \
    APU/VRC6.CPP \
    APU/N163.CPP \
    APU/MMC5.CPP \
    APU/FDS.CPP \
    APU/DPCM.CPP \
    APU/APU.CPP \
    APU/VRC7.cpp \
    APU/Triangle.cpp \
    APU/Square.cpp \
    APU/S5B.cpp \
    APU/Noise.cpp \
    APU/Mixer.cpp \
    APU/FDSSound.cpp \
    APU/emu2413.c \
    APU/emu2149.c \
    Blip_Buffer/Blip_Buffer.cpp \
    FFT/Fft.cpp \
    ../../common/cqtmfc.cpp \
    FamiTrackerView.cpp \
    FamiTracker.cpp \
    DirectSound.cpp \
    SWSpectrum.cpp \
    SWSampleScope.cpp \
    SampleWindow.cpp \
    GraphEditor.cpp \
    SequenceEditor.cpp \
    SizeEditor.cpp \
    SequenceSetting.cpp \
    InstrumentEditor2A03.cpp \
    InstrumentEditPanel.cpp \
    InstrumentEditDlg.cpp \
    InstrumentEditorDPCM.cpp \
    SampleEditorDlg.cpp \
    PCMImport.cpp \
    resampler/sinc.cpp \
    resampler/resample.inl \
    resampler/resample.cpp \
    cqtmfc_famitracker.cpp \
    InstrumentEditorVRC7.cpp \
    InstrumentEditorVRC6.cpp \
    InstrumentEditorFDS.cpp \
    InstrumentN163.cpp \
    WaveEditor.cpp \
    ModSequenceEditor.cpp \
    InstrumentEditorFDSEnvelope.cpp \
    InstrumentEditorN163Wave.cpp \
    InstrumentEditorN163.cpp \
    InstrumentEditorS5B.cpp \
    ChannelsDlg.cpp \
    ModulePropertiesDlg.cpp \
    ModuleImportDlg.cpp \
    SpeedDlg.cpp \
    SWLogo.cpp \
    WavProgressDlg.cpp \
    WaveFile.cpp \
    ControlPanelDlg.cpp \
    CustomControls.cpp \
    ExportDialog.cpp \
    CustomExporters.cpp \
    CustomExporter.cpp \
    CustomExporter_C_Interface.cpp \
    Compiler.cpp \
    Chunk.cpp \
    ChunkRender.cpp \
    CommentsDlg.cpp \
    InstrumentFileTree.cpp \
    Accelerator.cpp \
    ConfigWindow.cpp \
    ConfigSound.cpp \
    ConfigShortcuts.cpp \
    ConfigMIDI.cpp \
    DialogReBar.cpp

HEADERS += \
    TrackerChannel.h \
    SoundGen.h \
    Settings.h \
    Sequence.h \
    PatternEditor.h \
    PatternData.h \
    PatternCompiler.h \
    MainFrm.h \ 
    Instrument.h \
    Graphics.h \
    FrameEditor.h \
    FamiTrackerTypes.h \
    FamiTrackerDoc.h \
    Driver.h \
    DocumentFile.h \
    CustomExporterInterfaces.h \
    Compiler.h \
    Common.h \
    ColorScheme.h \
    Chunk.h \
    ChannelsVRC7.h \
    ChannelsVRC6.h \
    ChannelsS5B.h \
    ChannelsN163.h \
    ChannelsMMC5.h \
    ChannelsFDS.h \
    Channels2A03.h \
    ChannelMap.h \
    ChannelHandler.h \
    Action.h \
    APU/vrc7tone.h \
    APU/VRC7.h \
    APU/VRC6.H \
    APU/Triangle.h \
    APU/Square.h \
    APU/S5B.h \
    APU/Noise.h \
    APU/N163.H \
    APU/MMC5.H \
    APU/Mixer.h \
    APU/FDSSound.h \
    APU/FDS.H \
    APU/External.h \
    APU/emu2413.h \
    APU/emu2149.h \
    APU/DPCM.h \
    APU/Channel.h \
    APU/APU.h \
    APU/2413tone.h \
    Blip_Buffer/Blip_Buffer.h \
    drivers/drv_vrc7.h \
    drivers/drv_vrc6.h \
    drivers/drv_n163.h \
    drivers/drv_mmc5.h \
    drivers/drv_fds.h \
    drivers/drv_2a03.h \
    drivers/config.h \
    FFT/Fft.h \
    FFT/Complex.h \
    ../../common/cqtmfc.h \
    FamiTrackerView.h \
    FamiTracker.h \
    stdafx.h \
    DirectSound.h \
    resource.h \
    SWSpectrum.h \
    SWSampleScope.h \
    SampleWindow.h \
    GraphEditor.h \
    SequenceEditor.h \
    SizeEditor.h \
    SequenceSetting.h \
    InstrumentEditor2A03.h \
    InstrumentEditPanel.h \
    InstrumentEditDlg.h \
    InstrumentEditorDPCM.h \
    SampleEditorDlg.h \
    PCMImport.h \
    resampler/sinc.hpp \
    resampler/resample.hpp \
    cqtmfc_famitracker.h \
    InstrumentEditorVRC7.h \
    InstrumentEditorVRC6.h \
    InstrumentEditorFDS.h \
    WaveEditor.h \
    ModSequenceEditor.h \
    InstrumentEditorFDSEnvelope.h \
    InstrumentEditorN163Wave.h \
    InstrumentEditorN163.h \
    InstrumentEditorS5B.h \
    ChannelsDlg.h \
    ModulePropertiesDlg.h \
    ModuleImportDlg.h \
    SpeedDlg.h \
    SWLogo.h \
    WavProgressDlg.h \
    WaveFile.h \ 
    ControlPanelDlg.h \
    CustomControls.h \
    ExportDialog.h \
    CustomExporters.h \
    CustomExporter.h \
    CustomExporter_C_Interface.h \
    ChunkRender.h \
    CommentsDlg.h \
    InstrumentFileTree.h \
    Accelerator.h \
    ConfigWindow.h \
    ConfigSound.h \
    ConfigShortcuts.h \
    ConfigMIDI.h \
    DialogReBar.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEABB3021
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = famitracker.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

win32 {
    HEADERS += stdafx.h
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

unix:mac {
	# windows.h and co.
	NIX_CFLAGS = -I /usr/local/include/wine/windows -DWINE_UNICODE_NATIVE
	# stdafx.h
	NIX_CFLAGS += -I $$DEPENDENCYPATH
	NIX_CFLAGS += -I $$DEPENDENCYPATH/stdafxhack
    #HEADERS += $$DEPENDENCYPATH/stdafx.h
    QMAKE_CC = gcc
    QMAKE_CXX = g++
	QMAKE_CFLAGS   += $$NIX_CFLAGS
	QMAKE_CXXFLAGS += $$NIX_CFLAGS
}

OTHER_FILES += \
    famitracker-lib.pro

FORMS +=

RESOURCES += \
    $$TOP/common/resource.qrc
