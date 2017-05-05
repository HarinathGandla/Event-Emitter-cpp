noinst_LTLIBRARIES = libeventemittercpptest.la
libeventemittercpptest_la_CPPFLAGS = -I$(top_srcdir)/src
libeventemittercpptest_la_SOURCES =						\
	event/eventemittertest.h


noinst_PROGRAMS=eventemittercpptest
eventemittercpptest_LDADD = $(top_builddir)/src/libeventemittercpp.la $(top_builddir)/test/libeventemittercpptest.la 
eventemittercpptest_CPPFLAGS =  		-I$(top_srcdir)/src		\
				-I$(top_srcdir)/test

eventemittercpptest_LDFLAGS = 

eventemittercpptest_SOURCES=main.cpp
