AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
EXTRA_DIST = test_event_basic test_all_events test_syscall \
		test_clock_override test_rotation_destroy_flush \
		test_select_poll_epoll

noinst_PROGRAMS = select_poll_epoll
select_poll_epoll_SOURCES = select_poll_epoll.c
select_poll_epoll_LDADD = -lpthread -lpopt
select_poll_epoll_CFLAGS = -fno-stack-protector -D_FORTIFY_SOURCE=0

all-local:
	@if [ x"$(srcdir)" != x"$(builddir)" ]; then \
		for script in $(EXTRA_DIST); do \
			cp -f $(srcdir)/$$script $(builddir); \
		done; \
	fi

clean-local:
	@if [ x"$(srcdir)" != x"$(builddir)" ]; then \
		for script in $(EXTRA_DIST); do \
			rm -f $(builddir)/$$script; \
		done; \
	fi
