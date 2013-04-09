cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  libblinkm
  VERSION 0.1
  RELEASE alpha
  SUMMARY "Driver library for BlinkM smart LED device."
  AUTHOR "Ralf Kaestner"
  CONTACT "ralf.kaestner@gmail.com"
  HOME "http://github.com/kralf/libblinkm"
  LICENSE "GNU Lesser General Public License (LGPL)"
  PREFIX blinkm-
  INSTALL /usr
)

remake_doc(
  html
)

remake_pack_deb(
)
remake_pack_deb(
  COMPONENT utils
  DESCRIPTION "utilities"
  DEPENDS libblinkm
)
remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "development headers"
  DEPENDS libblinkm
)
remake_pack_deb(
  ARCH all
  COMPONENT doc
  DESCRIPTION "documentation"
)

remake_distribute_deb(
  DISTRIBUTION lucid
  SECTION libs
  UPLOAD ppa:kralf/naro
  DEPENDS remake doxygen
  PASS CMAKE_BUILD_TYPE LIBPOLOLU_GIT_REVISION
)
remake_distribute_deb(
  DISTRIBUTION precise
  SECTION libs
  UPLOAD ppa:kralf/naro
  DEPENDS remake doxygen
  PASS CMAKE_BUILD_TYPE LIBBLINKM_GIT_REVISION
)
