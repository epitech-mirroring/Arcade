/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/Json.hpp"
#include <fstream>
#include "criterion/criterion.h"
#include <cstdio>

Test(json_save, empty_json)
{
    JsonObject json = JsonObject();
    JsonObject n = JsonObject("null");
    n.setNull(true);
    json.addValue(n);
    json.writeToFile("tests/s_empty.json");

    // Check if the file is present
    std::ifstream f1("tests/s_empty.json");
    cr_assert(f1.is_open());

    // Check if the file only contains {"null": null}
    std::string content((std::istreambuf_iterator<char>(f1)),
                        std::istreambuf_iterator<char>());

    cr_assert_eq(content, "{\"null\":null}");

    // Delete the file
    std::remove("tests/s_empty.json");
}

Test(json_save, simple_json)
{
    JsonObject json = JsonObject();
    JsonString s = JsonString("string", "value");
    JsonInt i = JsonInt("int", 42);
    JsonBoolean b = JsonBoolean("bool", true);
    JsonObject n = JsonObject("null");
    n.setNull(true);
    //TODO JsonFloat f = JsonFloat("float", 3.14f);
    json.addValue(s);
    json.addValue(i);
    json.addValue(b);
    json.addValue(n);
    //TODO json.addValue(f);
    json.writeToFile("tests/s_simple.json");

    // Check if the file is present
    std::ifstream f1("tests/s_simple.json");
    cr_assert(f1.is_open());

    std::string content((std::istreambuf_iterator<char>(f1)),
                        std::istreambuf_iterator<char>());

    cr_assert(content[0] == '{');
    cr_assert(content[content.size() - 1] == '}');
    // Check with find because the order of the keys is not guaranteed
    cr_assert(content.find("\"string\":\"value\"") != std::string::npos);
    cr_assert(content.find("\"int\":42") != std::string::npos);
    cr_assert(content.find("\"bool\":true") != std::string::npos);
    cr_assert(content.find("\"null\":null") != std::string::npos);
    //TODO cr_assert(content.find("\"float\":3.14") != std::string::npos);

    // Count commas
    cr_assert_eq(std::count(content.begin(), content.end(), ','), 3);

    // Delete the file
    std::remove("tests/s_simple.json");
}

Test(json_save, array_of_int)
{
    JsonObject json = JsonObject();

    JsonArray array = JsonArray("int");
    JsonInt i1 = JsonInt("", 42);
    array.addValue(i1);
    JsonInt i2 = JsonInt("", 43);
    array.addValue(i2);
    JsonInt i3 = JsonInt("", 44);
    array.addValue(i3);

    json.addValue(array);

    json.writeToFile("tests/s_array_of_int.json");

    // Check if the file is present
    std::ifstream f1("tests/s_array_of_int.json");
    cr_assert(f1.is_open());

    // Check if the file only contains {"int":[42,43,44]}
    std::string content((std::istreambuf_iterator<char>(f1)),
                        std::istreambuf_iterator<char>());

    cr_assert_eq(content, "{\"int\":[42,43,44]}");
    // Delete the file
    std::remove("tests/s_array_of_int.json");
}

Test(json_save, obj_array)
{
    JsonObject json = JsonObject();

    JsonArray array = JsonArray("array");
    JsonObject obj1 = JsonObject("obj1");
    JsonObject obj2 = JsonObject("obj2");
    JsonString s = JsonString("string", "value");
    obj1.addValue(s);
    JsonInt i = JsonInt("int", 42);
    obj2.addValue(i);
    array.addValue(obj1);
    array.addValue(obj2);

    json.addValue(array);
    json.writeToFile("tests/s_obj_array.json");

    // Check if the file is present
    std::ifstream f1("tests/s_obj_array.json");
    cr_assert(f1.is_open());

    // Check if the file only contains {"array":[{"string":"value"},{"int":42}]}
    std::string content((std::istreambuf_iterator<char>(f1)),
                        std::istreambuf_iterator<char>());

    cr_assert_eq(content, "{\"array\":[{\"string\":\"value\"},{\"int\":42}]}");

    // Delete the file
    std::remove("tests/s_obj_array.json");
}
