#include "gcj2wgs.h"
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <rapidxml/rapidxml_print.hpp>
#include <string.h>
#include <sstream>
#include <fstream>

template <class Ch>
static rapidxml::xml_node<Ch>* correct(rapidxml::memory_pool<Ch>* pool, rapidxml::xml_node<Ch>* node, rapidxml::xml_node<Ch>* result = 0)
{
	if (node->type() != rapidxml::node_document && node->type() != rapidxml::node_element)
	{
		return pool->clone_node(node, result);
	}
	
	if (!result)
	{
		result = pool->allocate_node(node->type());
	}

	result->name(node->name(), node->name_size());

	for (rapidxml::xml_attribute<Ch>* i = node->first_attribute(); i; i = i->next_attribute())
	{
		result->append_attribute(pool->allocate_attribute(i->name(), i->value(), i->name_size(), i->value_size()));
	}

	if (strcmp(node->name(), "coordinates") == 0)
	{
		for (size_t i = 0; i < node->value_size(); ++i)
		{
			if (node->value()[i] == ',')
			{
				node->value()[i] = ' ';
			}
		}

		double x, y, z;
		std::stringstream in(node->value());
		std::stringstream out;

		while (in >> x >> y >> z)
		{
			gcj2wgs(y, x, &y, &x);
			out.precision(16);
			out.setf(std::ios::fixed);
			out << x << ',' << y << ',' << z << std::endl;
		}

		result->value(pool->allocate_string(out.str().c_str()));
	}
	else
	{
		result->value(node->value(), node->value_size());

		for (rapidxml::xml_node<Ch>* i = node->first_node(); i; i = i->next_sibling())
		{
			result->append_node(correct(pool, i));
		}
	}

	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		puts("Usage: kml-corrector <input_file> <output_file>");
		return -1;
	}

	rapidxml::file<> fin(argv[1]);
	rapidxml::xml_document<> doc;
	doc.parse<0>(fin.data());

	rapidxml::xml_document<> res;
	rapidxml::xml_node<>* node = doc.allocate_node(rapidxml::node_declaration);
	node->append_attribute(doc.allocate_attribute("version", "1.0"));
	node->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
	res.append_node(node);
	correct(&doc, &doc, &res);

	std::ofstream fout(argv[2]);
	fout << res;

	puts("Complete!");

	return 0;
}
