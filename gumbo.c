#include "php5_gumbo.h"
#include "gumbo.h"

zend_class_entry *gumbo_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_gumbo_load, 0, 0, 1)
	ZEND_ARG_INFO(0, html)
ZEND_END_ARG_INFO()

static zend_function_entry gumbo_functions[] = {
	{ NULL, NULL, NULL }
};

static zend_function_entry gumbo_class_methods[] =
{
	PHP_ME(gumbo_class,	load, arginfo_gumbo_load, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
{
	NULL, NULL, NULL
}
};

void build_dom(GumboNode* node) {
	//php_printf(node->v.text.text);

	//if (node->type != GUMBO_NODE_ELEMENT) {
	//	return;
	//}

	//GumboAttribute* href;
	//if (node->v.element.tag == GUMBO_TAG_A &&
	//	(href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
	//	std::cout << href->value << std::endl;
	//}

	//GumboVector* children = &node->v.element.children;
	//for (unsigned int i = 0; i < children->length; ++i) {
	//	search_for_links(static_cast<GumboNode*>(children->data[i]));
	//}
}


PHP_METHOD(gumbo_class, load) {
	zval *zv_html;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &zv_html) == FAILURE) {
		// @TODO: Throw exception

			RETURN_BOOL(false);
	}

	convert_to_string(zv_html);

	GumboOutput* output = gumbo_parse(Z_STRVAL_P(zv_html));

	// Create root DOMNode

	zval dom_node;
	object_init_ex(&dom_node, dom_node_class_entry);

	//zend_update_property(test_ce, obj, "foo", sizeof("foo") - 1, new_foo_value TSRMLS_CC);

	//ZVAL_STRING(&dom_constructor, ZEND_CONSTRUCTOR_FUNC_NAME);

	//ZVAL_NULL(&dom_params[0]);
	//ZVAL_NULL(&dom_params[1]);

	//if (call_user_function(NULL, &dom_document, &dom_constructor, &dom_ret, 2, dom_params) == FAILURE) {
	//	php_error_docref(NULL, E_ERROR, "Error calling constructor");
	//}

	//zval_dtor(&dom_constructor);
	//zval_dtor(&dom_ret);
	//zval_dtor(&dom_params);
	
	build_dom(output->root);

	gumbo_destroy_output(&kGumboDefaultOptions, output);
	//zval_ptr_dtor(&tmp_soap);

	// Return DOMDocument

	RETURN_ZVAL(&dom_node, 0, 0);
}

PHP_MINIT_FUNCTION(gumbo)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "Layershifter\\Gumbo", gumbo_class_methods);
	zend_register_internal_class(&ce);

	return SUCCESS;
}

zend_module_entry gumbo_module_entry =
{
	STANDARD_MODULE_HEADER,		/* Standard module header */
	PHP_GUMBO_EXTNAME,			/* Extension name */
	gumbo_functions,			/* Functions */
	PHP_MINIT(gumbo),			/* MINIT */
	NULL,						/* MSHUTDOWN */
	NULL,						/* RINIT */
	NULL,						/* RSHUTDOWN */
	NULL,						/* MINFO */
	PHP_GUMBO_VERSION,			/* Version */
	STANDARD_MODULE_PROPERTIES	/* Standard properties */
};

ZEND_GET_MODULE(gumbo)