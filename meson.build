project(
	'ddcbc-api',
	'c'
)

project_description = 'A basic API for controlling brightness via ddcutil api, and a basic CLI interface implemented for it.'

src = [ 'src/ddcbc-api.c' ]

inc = include_directories('include')

glibdep = dependency('glib-2.0')
ddcutildep = dependency('ddcutil')

libddcbc = library(meson.project_name(), src, install: true, include_directories: inc, dependencies: [ glibdep, ddcutildep ] )

libddcbc_dep = declare_dependency(include_directories: inc, link_with : libddcbc)
