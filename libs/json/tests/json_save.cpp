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
/**
Test(json_save, array_of_int)
{
json_object_t *json = create_json("root");

json_object_t *array = create_json_array("int");
append_json_array_int(array, 42);
append_json_array_int(array, 43);
append_json_array_int(array, 44);
add_json_array(json, array);

save_json_to_file(json, "tests/json/s_array_of_int.json");

// Check if the file is present
FILE *f1 = fopen("tests/json/s_array_of_int.json", "r");
cr_assert(f1 != NULL);

// Check if the file only contains {"null": null}
char *str = malloc(sizeof(char) * 105);
int size = fread(str, 1, 105, f1);
str[size] = '\0';
cr_assert_str_eq(str, "{\"int\":[42,43,44]}");

// Delete the file
remove("tests/json/s_array_of_int.json");
}

Test(json_save, obj_array)
{
json_object_t *json = create_json("root");

json_object_t *array = create_json_array("array");
json_object_t *obj1 = create_json("obj1");
json_object_t *obj2 = create_json("obj2");
add_json_string(obj1,
"string", "value");
add_json_int(obj2,
"int", 42);
append_json_array_object(array, obj1
);
append_json_array_object(array, obj2
);
add_json_array(json, array
);
save_json_to_file(json,
"tests/json/s_obj_array.json");

// Check if the file is present
FILE *f1 = fopen("tests/json/s_obj_array.json", "r");
cr_assert(f1
!= NULL);

// Check if the file only contains
char *str = malloc(sizeof(char) * 105);
int size = fread(str, 1, 105, f1);
str[size] = '\0';
cr_assert_str_eq(str,
"{\"array\":[{\"string\":\"value\"},{\"int\":42}]}");

// Delete the file
remove("tests/json/s_obj_array.json");
}**/