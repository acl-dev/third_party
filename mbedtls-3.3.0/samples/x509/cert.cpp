#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/ssl_ciphersuites.h"
#include "mbedtls/entropy.h"
#include "mbedtls/x509_crt.h"

int main(void) {
	const char* cert_file = "iq.crt";

	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context drbg;

	mbedtls_entropy_init(&entropy);
	mbedtls_ctr_drbg_init(&drbg);
	mbedtls_ssl_list_ciphersuites();


	mbedtls_x509_crt cert;
	mbedtls_x509_crt_init(&cert);
	int ret = mbedtls_x509_crt_parse_file(&cert, cert_file);
	if (ret != 0) {
		printf("parse file error=%d\r\n", ret);
		return 1;
	}

	printf("parse file ok\r\n");

	//mbedtls_x509_subject_alternative_name xsan;
	const mbedtls_x509_sequence* curr = &cert.subject_alt_names;

	char name[256];

	while (curr) {
		//memset(&xsan, 0, sizeof(xsan));

		/*
		ret = mbedtls_x509_parse_subject_alt_name(&curr->buf, &xsan);
		if (ret != 0) {
			printf("parse san error=%d\r\n", ret);
			return 1;
		}
		*/

		//printf("parse san ok\r\n");
		//switch (xsan.type) {
		switch (curr->buf.tag & MBEDTLS_X509_SAN_DNS_NAME) {
		case MBEDTLS_X509_SAN_DNS_NAME:
			memset(name, 0, sizeof(name));
			//memcpy(name, xsan.san.unstructured_name.p, xsan.san.unstructured_name.len);
			memcpy(name, curr->buf.p, curr->buf.len);
			printf("MBEDTLS_X509_SAN_DNS_NAME type, name=%s\r\n", name);
			break;
		default:
			//printf("type=%d\r\n", xsan.type);
			printf("type=%d\r\n", curr->buf.tag);
			break;
		}
		curr = curr->next;
	}

	mbedtls_x509_crt_free(&cert);
	return 0;
}
