##
## Auto Generated makefile, please do not edit
##
ProjectName:=aiapi

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./aiapi/Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "E:\trunk\Ahuman"
ProjectPath            := "E:\trunk\Ahuman"
CurrentFileName        :=
CurrentFulePath        :=
CurrentFileFullPath    :=
User                   :=mti00132
Date                   :=12/23/09
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
OutputFile             :=./lib/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." "$(IncludeSwitch)./aiapi/include" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/aiapi$(ObjectSuffix) $(IntermediateDirectory)/aiapiimpl$(ObjectSuffix) $(IntermediateDirectory)/aiapisocket$(ObjectSuffix) $(IntermediateDirectory)/string$(ObjectSuffix) $(IntermediateDirectory)/timer$(ObjectSuffix) $(IntermediateDirectory)/tinyxml$(ObjectSuffix) $(IntermediateDirectory)/tinyxmlerror$(ObjectSuffix) $(IntermediateDirectory)/tinyxmlparser$(ObjectSuffix) $(IntermediateDirectory)/xml$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@makedir $(@D)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) $(Objects)

./aiapi/Debug:
	@makedir "./aiapi/Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/aiapi$(ObjectSuffix): aiapi/src/aiapi.cpp $(IntermediateDirectory)/aiapi$(DependSuffix)
	@makedir "./aiapi/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiapi/src/aiapi.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aiapi$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aiapi$(DependSuffix): aiapi/src/aiapi.cpp
	@makedir "./aiapi/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aiapi$(ObjectSuffix) -MF$(IntermediateDirectory)/aiapi$(DependSuffix) -MM "E:/trunk/Ahuman/aiapi/src/aiapi.cpp"

$(IntermediateDirectory)/aiapiimpl$(ObjectSuffix): aiapi/src/aiapiimpl.cpp $(IntermediateDirectory)/aiapiimpl$(DependSuffix)
	@makedir "./aiapi/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiapi/src/aiapiimpl.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aiapiimpl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aiapiimpl$(DependSuffix): aiapi/src/aiapiimpl.cpp
	@makedir "./aiapi/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aiapiimpl$(ObjectSuffix) -MF$(IntermediateDirectory)/aiapiimpl$(DependSuffix) -MM "E:/trunk/Ahuman/aiapi/src/aiapiimpl.cpp"

$(IntermediateDirectory)/aiapisocket$(ObjectSuffix): aiapi/src/aiapisocket.cpp $(IntermediateDirectory)/aiapisocket$(DependSuffix)
	@makedir "./aiapi/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiapi/src/aiapisocket.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aiapisocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aiapisocket$(DependSuffix): aiapi/src/aiapisocket.cpp
	@makedir "./aiapi/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aiapisocket$(ObjectSuffix) -MF$(IntermediateDirectory)/aiapisocket$(DependSuffix) -MM "E:/trunk/Ahuman/aiapi/src/aiapisocket.cpp"

$(IntermediateDirectory)/string$(ObjectSuffix): aiapi/src/string.cpp $(IntermediateDirectory)/string$(DependSuffix)
	@makedir "./aiapi/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiapi/src/string.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/string$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/string$(DependSuffix): aiapi/src/string.cpp
	@makedir "./aiapi/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/string$(ObjectSuffix) -MF$(IntermediateDirectory)/string$(DependSuffix) -MM "E:/trunk/Ahuman/aiapi/src/string.cpp"

$(IntermediateDirectory)/timer$(ObjectSuffix): aiapi/src/timer.cpp $(IntermediateDirectory)/timer$(DependSuffix)
	@makedir "./aiapi/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiapi/src/timer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/timer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/timer$(DependSuffix): aiapi/src/timer.cpp
	@makedir "./aiapi/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/timer$(ObjectSuffix) -MF$(IntermediateDirectory)/timer$(DependSuffix) -MM "E:/trunk/Ahuman/aiapi/src/timer.cpp"

$(IntermediateDirectory)/tinyxml$(ObjectSuffix): aiapi/src/tinyxml.cpp $(IntermediateDirectory)/tinyxml$(DependSuffix)
	@makedir "./aiapi/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiapi/src/tinyxml.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tinyxml$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tinyxml$(DependSuffix): aiapi/src/tinyxml.cpp
	@makedir "./aiapi/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/tinyxml$(ObjectSuffix) -MF$(IntermediateDirectory)/tinyxml$(DependSuffix) -MM "E:/trunk/Ahuman/aiapi/src/tinyxml.cpp"

$(IntermediateDirectory)/tinyxmlerror$(ObjectSuffix): aiapi/src/tinyxmlerror.cpp $(IntermediateDirectory)/tinyxmlerror$(DependSuffix)
	@makedir "./aiapi/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiapi/src/tinyxmlerror.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tinyxmlerror$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tinyxmlerror$(DependSuffix): aiapi/src/tinyxmlerror.cpp
	@makedir "./aiapi/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/tinyxmlerror$(ObjectSuffix) -MF$(IntermediateDirectory)/tinyxmlerror$(DependSuffix) -MM "E:/trunk/Ahuman/aiapi/src/tinyxmlerror.cpp"

$(IntermediateDirectory)/tinyxmlparser$(ObjectSuffix): aiapi/src/tinyxmlparser.cpp $(IntermediateDirectory)/tinyxmlparser$(DependSuffix)
	@makedir "./aiapi/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiapi/src/tinyxmlparser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tinyxmlparser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tinyxmlparser$(DependSuffix): aiapi/src/tinyxmlparser.cpp
	@makedir "./aiapi/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/tinyxmlparser$(ObjectSuffix) -MF$(IntermediateDirectory)/tinyxmlparser$(DependSuffix) -MM "E:/trunk/Ahuman/aiapi/src/tinyxmlparser.cpp"

$(IntermediateDirectory)/xml$(ObjectSuffix): aiapi/src/xml.cpp $(IntermediateDirectory)/xml$(DependSuffix)
	@makedir "./aiapi/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiapi/src/xml.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/xml$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/xml$(DependSuffix): aiapi/src/xml.cpp
	@makedir "./aiapi/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/xml$(ObjectSuffix) -MF$(IntermediateDirectory)/xml$(DependSuffix) -MM "E:/trunk/Ahuman/aiapi/src/xml.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/aiapi$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aiapi$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aiapi$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/aiapiimpl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aiapiimpl$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aiapiimpl$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/aiapisocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aiapisocket$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aiapisocket$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/string$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/string$(DependSuffix)
	$(RM) $(IntermediateDirectory)/string$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/timer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/timer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/timer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tinyxmlerror$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tinyxmlerror$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tinyxmlerror$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tinyxmlparser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tinyxmlparser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tinyxmlparser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/xml$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/xml$(DependSuffix)
	$(RM) $(IntermediateDirectory)/xml$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


