##
## Auto Generated makefile, please do not edit
##
ProjectName:=moddb

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./aiengine/Debug
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
IncludePath            := "$(IncludeSwitch)." "$(IncludeSwitch)./aiengine/include" "$(IncludeSwitch)./aiengine/src/include" "$(IncludeSwitch)./generic/include" "$(IncludeSwitch)./generic/include/stacktrace"  "$(IncludeSwitch)." "$(IncludeSwitch)." "$(IncludeSwitch)./aiengine/include" "$(IncludeSwitch)./aiengine/src/include" "$(IncludeSwitch)./generic/include" "$(IncludeSwitch)./generic/include/stacktrace" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/db$(ObjectSuffix) $(IntermediateDirectory)/dbcursor$(ObjectSuffix) $(IntermediateDirectory)/dbfile$(ObjectSuffix) $(IntermediateDirectory)/dbrecordheader$(ObjectSuffix) $(IntermediateDirectory)/dbrecordset$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@makedir $(@D)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) $(Objects)

./aiengine/Debug:
	@makedir "./aiengine/Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/db$(ObjectSuffix): aiengine/src/moddb/db.cpp $(IntermediateDirectory)/db$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/moddb/db.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/db$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/db$(DependSuffix): aiengine/src/moddb/db.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/db$(ObjectSuffix) -MF$(IntermediateDirectory)/db$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/moddb/db.cpp"

$(IntermediateDirectory)/dbcursor$(ObjectSuffix): aiengine/src/moddb/dbcursor.cpp $(IntermediateDirectory)/dbcursor$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/moddb/dbcursor.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dbcursor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dbcursor$(DependSuffix): aiengine/src/moddb/dbcursor.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/dbcursor$(ObjectSuffix) -MF$(IntermediateDirectory)/dbcursor$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/moddb/dbcursor.cpp"

$(IntermediateDirectory)/dbfile$(ObjectSuffix): aiengine/src/moddb/dbfile.cpp $(IntermediateDirectory)/dbfile$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/moddb/dbfile.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dbfile$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dbfile$(DependSuffix): aiengine/src/moddb/dbfile.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/dbfile$(ObjectSuffix) -MF$(IntermediateDirectory)/dbfile$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/moddb/dbfile.cpp"

$(IntermediateDirectory)/dbrecordheader$(ObjectSuffix): aiengine/src/moddb/dbrecordheader.cpp $(IntermediateDirectory)/dbrecordheader$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/moddb/dbrecordheader.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dbrecordheader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dbrecordheader$(DependSuffix): aiengine/src/moddb/dbrecordheader.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/dbrecordheader$(ObjectSuffix) -MF$(IntermediateDirectory)/dbrecordheader$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/moddb/dbrecordheader.cpp"

$(IntermediateDirectory)/dbrecordset$(ObjectSuffix): aiengine/src/moddb/dbrecordset.cpp $(IntermediateDirectory)/dbrecordset$(DependSuffix)
	@makedir "./aiengine/Debug"
	$(CompilerName) $(SourceSwitch) "E:/trunk/Ahuman/aiengine/src/moddb/dbrecordset.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dbrecordset$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dbrecordset$(DependSuffix): aiengine/src/moddb/dbrecordset.cpp
	@makedir "./aiengine/Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/dbrecordset$(ObjectSuffix) -MF$(IntermediateDirectory)/dbrecordset$(DependSuffix) -MM "E:/trunk/Ahuman/aiengine/src/moddb/dbrecordset.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/db$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/db$(DependSuffix)
	$(RM) $(IntermediateDirectory)/db$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dbcursor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dbcursor$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dbcursor$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dbfile$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dbfile$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dbfile$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dbrecordheader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dbrecordheader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dbrecordheader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dbrecordset$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dbrecordset$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dbrecordset$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


