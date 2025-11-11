cmake_minimum_required(VERSION 2.8)

#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Release CACHE STRING "set build type to release")

#message(project_dir=${PROJECT_SOURCE_DIR})

if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	message(FATAL_ERROR "Please into another dir to build!")
endif()

message(STATUS "ndk=${CMAKE_ANDROID_NDK}")

#string(TOUPPER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME)
if (CMAKE_SYSTEM_NAME MATCHES "Android")
    message(STATUS "current ndk path: ${CMAKE_ANDROID_NDK}")

	add_definitions("-O0 -DANDROID")
	add_definitions("-fvisibility=hidden")
	add_definitions("-fvisibility-inlines-hidden")
	add_definitions("-Wno-unused-command-line-argument")
	add_definitions("-fdata-sections -ffunction-sections")
	string(APPEND CMAKE_C_FLAGS " -Qunused-arguments")
	set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "OHOS")
    message(STATUS "current ndk path: ${CMAKE_ANDROID_NDK}")

	add_definitions("-O0 -DANDROID")
	add_definitions("-fvisibility=hidden")
	add_definitions("-fvisibility-inlines-hidden")
	add_definitions("-Wno-unused-command-line-argument")
	add_definitions("-fdata-sections -ffunction-sections")
	string(APPEND CMAKE_C_FLAGS " -Qunused-arguments")
	set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
	add_definitions("-Os -fdata-sections -ffunction-sections")
	set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	add_definitions("-fvisibility=hidden")
	add_definitions("-fvisibility-inlines-hidden")
	add_definitions("-Os -fdata-sections -ffunction-sections")
	set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-dead_strip")
	set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
	add_definitions("-O2")
	set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(WIN_OS true)
else()
	message(FATAL_ERROR "unknown CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
endif()

##############################################################################

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(src_path ${CMAKE_CURRENT_SOURCE_DIR}/library)
set(src_crypto
	${src_path}/aes.c
    ${src_path}/aesni.c
    ${src_path}/aesce.c
    ${src_path}/aria.c
    ${src_path}/asn1parse.c
    ${src_path}/asn1write.c
    ${src_path}/base64.c
    ${src_path}/bignum.c
    ${src_path}/bignum_core.c
    ${src_path}/bignum_mod.c
    ${src_path}/bignum_mod_raw.c
    ${src_path}/block_cipher.c
    ${src_path}/camellia.c
    ${src_path}/ccm.c
    ${src_path}/chacha20.c
    ${src_path}/chachapoly.c
    ${src_path}/cipher.c
    ${src_path}/cipher_wrap.c
    ${src_path}/constant_time.c
    ${src_path}/cmac.c
    ${src_path}/ctr_drbg.c
    ${src_path}/des.c
    ${src_path}/dhm.c
    ${src_path}/ecdh.c
    ${src_path}/ecdsa.c
    ${src_path}/ecjpake.c
    ${src_path}/ecp.c
    ${src_path}/ecp_curves.c
    ${src_path}/ecp_curves_new.c
    ${src_path}/entropy.c
    ${src_path}/entropy_poll.c
    ${src_path}/error.c
    ${src_path}/gcm.c
    ${src_path}/hkdf.c
    ${src_path}/hmac_drbg.c
    ${src_path}/lmots.c
    ${src_path}/lms.c
    ${src_path}/md.c
    ${src_path}/md5.c
    ${src_path}/memory_buffer_alloc.c
    ${src_path}/nist_kw.c
    ${src_path}/oid.c
    ${src_path}/padlock.c
    ${src_path}/pem.c
    ${src_path}/pk.c
    ${src_path}/pk_ecc.c
    ${src_path}/pk_wrap.c
    ${src_path}/pkcs12.c
    ${src_path}/pkcs5.c
    ${src_path}/pkparse.c
    ${src_path}/pkwrite.c
    ${src_path}/platform.c
    ${src_path}/platform_util.c
    ${src_path}/poly1305.c
    ${src_path}/psa_crypto.c
    ${src_path}/psa_crypto_aead.c
    ${src_path}/psa_crypto_cipher.c
    ${src_path}/psa_crypto_client.c
    ${src_path}/psa_crypto_driver_wrappers_no_static.c
    ${src_path}/psa_crypto_ecp.c
    ${src_path}/psa_crypto_ffdh.c
    ${src_path}/psa_crypto_hash.c
    ${src_path}/psa_crypto_mac.c
    ${src_path}/psa_crypto_pake.c
    ${src_path}/psa_crypto_rsa.c
    ${src_path}/psa_crypto_se.c
    ${src_path}/psa_crypto_slot_management.c
    ${src_path}/psa_crypto_storage.c
    ${src_path}/psa_its_file.c
    ${src_path}/psa_util.c
    ${src_path}/ripemd160.c
    ${src_path}/rsa.c
    ${src_path}/rsa_alt_helpers.c
    ${src_path}/sha1.c
    ${src_path}/sha256.c
    ${src_path}/sha512.c
    ${src_path}/sha3.c
    ${src_path}/threading.c
    ${src_path}/timing.c
    ${src_path}/version.c
    ${src_path}/version_features.c
)

set(src_x509
    ${src_path}/pkcs7.c
    ${src_path}/x509.c
    ${src_path}/x509_create.c
    ${src_path}/x509_crl.c
    ${src_path}/x509_crt.c
    ${src_path}/x509_csr.c
    ${src_path}/x509write.c
    ${src_path}/x509write_crt.c
    ${src_path}/x509write_csr.c
)

set(src_tls
    ${src_path}/debug.c
    ${src_path}/mps_reader.c
    ${src_path}/mps_trace.c
    ${src_path}/net_sockets.c
    ${src_path}/ssl_cache.c
    ${src_path}/ssl_ciphersuites.c
    ${src_path}/ssl_client.c
    ${src_path}/ssl_cookie.c
    ${src_path}/ssl_debug_helpers_generated.c
    ${src_path}/ssl_msg.c
    ${src_path}/ssl_ticket.c
    ${src_path}/ssl_tls.c
    ${src_path}/ssl_tls12_client.c
    ${src_path}/ssl_tls12_server.c
    ${src_path}/ssl_tls13_keys.c
    ${src_path}/ssl_tls13_server.c
    ${src_path}/ssl_tls13_client.c
    ${src_path}/ssl_tls13_generic.c
)

set(src_all ${src_tls} ${src_x509} ${src_crypto})

##############################################################################

if (${UNIX_OS})
	add_definitions(
		"-W"
		"-fPIC"
		"-Wall"
		"-Werror"
		"-Wshadow"
		"-Wpointer-arith"
		"-Waggregate-return"
		"-Wmissing-prototypes"
		"-D_REENTRANT"
		"-D_USE_FAST_MACRO"
		"-Wno-long-long"
		"-Wuninitialized"
		"-D_POSIX_PTHREAD_SEMANTICS"
		"-Wstrict-prototypes"
		"-D_FILE_OFFSET_BITS=64"
	)

	if (CMAKE_COMPILER_IS_GNUCC)
		execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
			OUTPUT_VARIABLE GCC_VERSION)
		string(REGEX MATCHALL "[0-9]+" GCC_VERSION_COMPONENTS ${GCC_VERSION})
		list(GET GCC_VERSION_COMPONENTS 0 GCC_MAJOR)
#		list(GET GCC_VERSION_COMPONENTS 1 GCC_MINOR)

		if(CMAKE_VERSION GREATER "3.0")
#			if ((GCC_MAJOR GREATER_EQUAL 4) AND (GCC_MINOR GREATER_EQUAL 8))
				message(STATUS "gcc version major=${GCC_MAJOR}")
#				message(STATUS "gcc version minor=${GCC_MINOR}")
#			endif()
		endif()
	endif()

	if (!CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
		add_definitions("-Wno-invalid-source-encoding")
	endif()

	if (CMAKE_SYSTEM_NAME MATCHES "Android")
		add_definitions("-Wno-inline-asm -D_SOCKLEN_T")
	endif()

	if (CMAKE_SYSTEM_NAME MATCHES "OHOS")
		add_definitions("-Wno-inline-asm -D_SOCKLEN_T")
	endif()

	if (CMAKE_BUILD_TYPE STREQUAL "RELEASE")
		#add_definitions("-Os")
	else()
		add_definitions("-g")
	endif()
elseif (${WIN_OS})
	add_definitions("-Yc -D_WINSOCK_DEPRECATED_NO_WARNINGS")
endif()

if (CMAKE_SYSTEM_NAME MATCHES "Android")
	set(CMAKE_SHARED_LINKER_FLAGS "-shared")
	set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/android/lib/${ANDROID_ABI})
	set(LIBRARY_OUTPUT_PATH ${lib_output_path})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${lib_output_path})

	add_library(mbedcrypto_static STATIC ${src_crypto})
	SET_TARGET_PROPERTIES(mbedcrypto_static PROPERTIES OUTPUT_NAME "mbedcrypto")

    add_library(mbedtls_all_static STATIC ${src_all})
	SET_TARGET_PROPERTIES(mbedtls_all_static PROPERTIES OUTPUT_NAME "mbedtls_all")

	link_directories(${lib_output_path})
elseif (CMAKE_SYSTEM_NAME MATCHES "OHOS")
	set(CMAKE_SHARED_LINKER_FLAGS "-shared")
	set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/harmony/lib/${OHOS_ARCH})
	set(LIBRARY_OUTPUT_PATH ${lib_output_path})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${lib_output_path})

	add_library(mbedcrypto_static STATIC ${src_crypto})
	SET_TARGET_PROPERTIES(mbedcrypto_static PROPERTIES OUTPUT_NAME "mbedcrypto")

    add_library(mbedtls_all_static STATIC ${src_all})
	SET_TARGET_PROPERTIES(mbedtls_all_static PROPERTIES OUTPUT_NAME "mbedtls_all")

	link_directories(${lib_output_path})
else()
	set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/lib)
	set(LIBRARY_OUTPUT_PATH ${lib_output_path})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${lib_output_path})

	add_library(mbedcrypto_static STATIC ${src_crypto})
	SET_TARGET_PROPERTIES(mbedcrypto_static PROPERTIES OUTPUT_NAME "mbedcrypto")

    add_library(mbedtls_all_static STATIC ${src_all})
	SET_TARGET_PROPERTIES(mbedtls_all_static PROPERTIES OUTPUT_NAME "mbedtls_all")

	if (${WIN_OS})
		set(CMAKE_SHARED_LINKER_FLAGS "/DYNAMICBASE ws2_32.lib IPHlpApi.lib")
	endif()
endif()

add_library(mbedcrypto SHARED ${src_crypto})
add_library(mbedtls_all SHARED ${src_all})

##############################################################################
