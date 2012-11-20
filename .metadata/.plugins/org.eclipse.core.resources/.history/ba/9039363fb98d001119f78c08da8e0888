SOURCES = $(foreach file, $(shell ls src/*.cpp), $(basename $(notdir $(file))))
OBJS = $(foreach file, $(SOURCES), obj/$(file).o)

TEST_SOURCES = $(foreach file, $(SOURCES), $(subst src/main.cpp, , $(file)))
#TEST_OBJS = $(foreach file, $(OBJS), $(subst obj/main.o, , $(file)))
TEST_OBJS = obj/test.o obj/StopWords.o obj/HTMLParser.o obj/URL.o obj/WordList.o obj/Word.o obj/Occurence.o obj/URLQueue.o obj/Page.o obj/StringURLResolver.o obj/WebCrawler.o obj/XMLGenerator.o

MAIN_SOURCES = $(foreach file, $(SOURCES), $(subst src/test.cpp, , $(file)))
MAIN_OBJS = $(foreach file, $(OBJS), $(subst obj/test.o, , $(file)))

LIBSOURCES = $(foreach file, $(shell ls cs240utils/src/*.cpp), $(basename $(notdir $(file))))
LIBOBJS = $(foreach file, $(LIBSOURCES), cs240utils/obj/$(file).o)

#BOOST = -l boost_regex

EXE = bin/crawler
TEST = bin/testcrawler

LIB = lib/libcs240utils.a

all: bin

#depend
bin : $(EXE)

run : all
	$(EXE) http://mormon.org/joseph-smith/ outputabby.xml stopwords.txt

test : depend $(TEST)
	$(TEST)

lib : $(LIB)

clean :
	-rm obj/*
	-rm bin/*
	-rm cs240utils/obj/*
	-rm lib/*

rebuild : clean exe

checkstyle :
	~cs240ta/bin/CppCheckStyle/CppCheckStyle inc/*.h
	
valgrind_test_crawler : test
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=string.supp bin/testcrawler

valgrind_main_crawler : run
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=string.supp bin/crawler

depend : 
	@-rm depend.mk
	@for f in $(SOURCES) ; do g++ -MM -MT obj/$$f.o -I inc/ -I cs240utils/inc/ src/$$f.cpp >> depend.mk; done
	@-rm cs240utils.mk
	@for f in $(LIBSOURCES) ; do g++ -MM -MT cs240utils/obj/$$f.o -I cs240utils/inc/ cs240utils/src/$$f.cpp >> cs240utils.mk; done

$(EXE) : $(MAIN_OBJS) $(LIB)
	g++ -o $(EXE) $(MAIN_OBJS) $(LIB)

$(TEST) : $(TEST_OBJS) $(LIB)
	g++ -g -o $(TEST) $(TEST_OBJS) $(LIB) $(BOOST) -I inc/

$(LIB) : $(LIBOBJS)
	ar r $(LIB) $(LIBOBJS)

obj/%.o : src/%.cpp
	g++ -g -c -I inc/ -I cs240utils/inc/ -o $@ $<

cs240utils/obj/%.o : cs240utils/src/%.cpp
	g++ -g -c -I cs240utils/inc/ -o $@ $<

include depend.mk
include cs240utils.mk