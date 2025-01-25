#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>

// Tạo enum để đại diện xử lý các kiểu dữ liệu có trong JSON
typedef enum
{
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

typedef struct JsonValue
{ // 1 thời điểm chỉ sử dụng 1 type, nên dùng Union: dùng để lưu trữ các biến
    JsonType type;
    union
    {
        int boolean;
        double number;
        char *string;
        struct
        {                             // Mảng sẽ có số lượng và kiểu dữ liệu của mảng. Những với Json sẽ có các giá trị với kiểu dữ liệu khác nhau
            struct JsonValue *values; // Vì value có nhiều kiểu dữ liệu khác nhau. Đệ quy JsonValue để lấy kiểu dữ liệu và giá trị của values để lưu vào từng biến tương ứng
            size_t count;   
        } array;
        struct
        {
            char **keys; // Mỗi *key là một chuỗi, được tập hợp bởi 1 mảng khác nên phải sử dụng con trỏ cấp 2 (chuỗi trong mảng) ["key1", "key2"]
            struct JsonValue *values;
            size_t count; // Tăng khi kiểm tra được 1 cặp key và value
        } object;
    } value;
} JsonValue;

JsonValue *parse_json(const char **json);

void free_json_value(JsonValue *json_value);

static void skip_whitespace(const char **json)
{
    while (isspace(**json))
    {
        (*json)++;
    }
}

JsonValue *parse_null(const char **json)
{
    skip_whitespace(json);
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue)); // Cấp phát 1 vùng nhớ để lưu giữ
    if (strncmp(*json, "null", 4) == 0)
    {                            // Strncmp: so sánh chuỗi hiện tại, quy định số byte để so sánh: 4 byte của "null"
        value->type = JSON_NULL; // Đặt kiểu dữ liệu NULL
        *json += 4;              // cộng chuỗi lên 4 ký tự để tiếp tục so sánh
        return value;            // value gồm type và giá trị null
    }
    free(value);
    return NULL;
}

JsonValue *parse_boolean(const char **json)
{
    skip_whitespace(json);
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
    if (strncmp(*json, "true", 4) == 0)
    {
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json += 4;
    }
    else if (strncmp(*json, "false", 5) == 0)
    {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json += 5;
    }
    else //fales, 
    {
        free(value);
        return NULL;
    }
    return value;
}

JsonValue *parse_number(const char **json)
{
    skip_whitespace(json);
    char *end;                        // Lưu địa chỉ các phần tử duyệt qua
    double num = strtod(*json, &end); // Chuyển chuỗi sang 1 số double strtod(const char *str, char **endptr), con trỏ end sẽ nằm tại ví trí cuối cùng của chuỗi, trước '\0'
    //"224354"
    //"324a43fc"

    if (end != *json)
    {
        JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
        value->type = JSON_NUMBER;
        value->value.number = num;
        *json = end;
        return value;
    }
    return NULL;
}

JsonValue *parse_string(const char **json)
{
    skip_whitespace(json);

    if (**json == '\"')
    {
        (*json)++;
        const char *start = *json;
        while (**json != '\"' && **json != '\0')
        { // Dich đến hết chuỗi
            (*json)++;
        }
        if (**json == '\"')
        {
            size_t length = *json - start;                           // 3
            char *str = (char *)malloc((length + 1) * sizeof(char)); // Cap phat length+1 byte cho ky tu NULL
            strncpy(str, start, length);                             // String n copy: copy length byte từ địa chỉ start vào chuỗi str
            str[length] = '\0';                                      // Them ky tu NULL vào chuỗi

            JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
            value->type = JSON_STRING;
            value->value.string = str;
            (*json)++;
            return value;
        }
    }
    return NULL;
}

JsonValue *parse_array(const char **json)
{
    skip_whitespace(json);
    if (**json == '[')
    {
        (*json)++;
        skip_whitespace(json);

        JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue));
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0;
        array_value->value.array.values = NULL;

        while (**json != ']' && **json != '\0')
        {
            JsonValue *element = parse_json(json); // 70
            if (element)
            {
                array_value->value.array.count++;
                array_value->value.array.values = (JsonValue *)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JsonValue));
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);
            }
            else
            {
                break;
            }
            skip_whitespace(json);
            if (**json == ',')
            {
                (*json)++;
            }
        }
        if (**json == ']')
        {
            (*json)++;
            return array_value;
        }
        else
        {
            free_json_value(array_value);
            return NULL;
        }
    }
    return NULL;
}

JsonValue *parse_object(const char **json)
{
    skip_whitespace(json);
    if (**json == '{')
    {
        (*json)++;
        skip_whitespace(json);

        JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue));
        object_value->type = JSON_OBJECT;
        object_value->value.object.count = 0;
        object_value->value.object.keys = NULL;
        object_value->value.object.values = NULL;

        while (**json != '}' && **json != '\0')
        {
            JsonValue *key = parse_string(json);
            if (key)
            {
                skip_whitespace(json);
                if (**json == ':')
                {
                    (*json)++;
                    JsonValue *value = parse_json(json);
                    if (value)
                    {
                        object_value->value.object.count++;
                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;

                        object_value->value.object.values = (JsonValue *)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JsonValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
                        free(value);
                    }
                    else
                    {
                        free_json_value(key);
                        break;
                    }
                }
                else
                {
                    free_json_value(key);
                    break;
                }
            }
            else
            {
                break;
            }
            skip_whitespace(json);
            if (**json == ',')
            {
                (*json)++;
            }
        }
        if (**json == '}')
        {
            (*json)++;
            return object_value;
        }
        else
        {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}

JsonValue *parse_json(const char **json)
{
    while (isspace(**json))
    { // Bỏ qua khoảng trắng
        (*json)++;
    }
    switch (**json)
    { // Xem xét các ký tự để chạy các lựa chọn
    case 'n'://null
        return parse_null(json);
    case 't'://true
    case 'f'://false
        return parse_boolean(json);
    case '\"':
        return parse_string(json);
    case '[':
        return parse_array(json);
    case '{':
        return parse_object(json);
    default:
        if (isdigit(**json) || **json == '-')
        {
            return parse_number(json);
        }
        else
        {
            printf("Cấu trúc Json không chính xác!");
            return NULL;
        }
    }
}

void free_json_value(JsonValue *json_value)
{
    if (json_value == NULL)
    {
        return;
    }

    switch (json_value->type)
    {
    case JSON_STRING:
        free(json_value->value.string);
        break;

    case JSON_ARRAY:
        for (size_t i = 0; i < json_value->value.array.count; i++)
        {
            free_json_value(&json_value->value.array.values[i]);
        }
        free(json_value->value.array.values);
        break;

    case JSON_OBJECT:
        for (size_t i = 0; i < json_value->value.object.count; i++)
        {
            free(json_value->value.object.keys[i]);
            free_json_value(&json_value->value.object.values[i]);
        }
        free(json_value->value.object.keys);
        free(json_value->value.object.values);
        break;

    default:
        break;
    }
}

void test(JsonValue *json_value)
{
    if (json_value != NULL && json_value->type == JSON_OBJECT)
    {
        // Truy cập giá trị của các trường trong đối tượng JSON
        size_t num_fields = json_value->value.object.count;
        size_t num_fields2 = json_value->value.object.values->value.object.count;
        for (size_t i = 0; i < num_fields; ++i)
        {

            char *key = json_value->value.object.keys[i];
            JsonValue *value = &json_value->value.object.values[i];

            JsonType type = (int)(json_value->value.object.values[i].type);// Đọc chính xác dữ liệu

            if (type == JSON_STRING)
            {
                printf("%s: %s\n", key, value->value.string);
            }

            if (type == JSON_NUMBER)
            {
                printf("%s: %f\n", key, value->value.number);
            }

            if (type == JSON_BOOLEAN)
            {
                printf("%s: %s\n", key, value->value.boolean ? "True" : "False");
            }

            if (type == JSON_OBJECT)
            {
                printf("%s: \n", key);
                test(value);
            }

            if (type == JSON_ARRAY)
            {
                printf("%s: ", key);
                for (int i = 0; i < value->value.array.count; i++)
                {
                    test(value->value.array.values + i);
                }
                printf("\n");
            }
        }
    }
    else
    {
        if (json_value->type == JSON_STRING)
        {
            printf("%s ", json_value->value.string);
        }

        if (json_value->type == JSON_NUMBER)
        {
            printf("%f ", json_value->value.number);
        }

        if (json_value->type == JSON_BOOLEAN)
        {
            printf("%s ", json_value->value.boolean ? "true" : "false");
        }

        if (json_value->type == JSON_OBJECT)
        {
            printf("%s: \n", json_value->value.object.keys);
            test(json_value->value.object.values);
        }
    }
}

int main(int argc, char const *argv[])
{
    // Chuỗi JSON đầu vào \" nhận biết chuỗi con bên trong chuỗi khác

    const char *json_str = "{"
                           "\"1001\":{"
                                "\"SoPhong\":null,"
                                "\"NguoiThue\":{"
                                    "\"Ten\":\"Nguyen Van A\","
                                    "\"CCCD\":\"1920517781\","
                                    "\"Tuoi\":26,"
                                    "\"ThuongTru\":{"
                                        "\"Duong\":\"73 Ba Huyen Thanh Quan\","
                                        "\"Phuong_Xa\":\"Phuong 6\","
                                        "\"Tinh_TP\":\"Ho Chi Minh\""
                                    "}"
                                "},"
                                "\"SoNguoiO\":{"
                                    "\"1\":\"Nguyen Van A\","
                                    "\"2\":\"Nguyen Van B\","
                                    "\"3\":\"Nguyen Van C\""
                                "},"
                                "\"TienDien\": [24, 56, 98],"
                                "\"TienNuoc\":30.000"
                           "},"
                           "\"1002\":{"
                                "\"SoPhong\":5,"
                                "\"NguoiThue\":{"
                                    "\"Ten\":\"Phan Hoang Trung\","
                                    "\"CCCD\":\"012345678912\","
                                    "\"Tuoi\":24,"
                                    "\"ThuongTru\":{"
                                        "\"Duong\":\"53 Le Dai Hanh\","
                                        "\"Phuong_Xa\":\"Phuong 11\","
                                        "\"Tinh_TP\":\"Ho Chi Minh\""
                                    "}"
                                "},"
                                "\"SoNguoiO\":{"
                                    "\"1\":\"Phan Van Nhat\","
                                    "\"2\":\"Phan Van Nhi\","
                                    "\"2\":\"Phan Van Tam\","
                                    "\"3\":\"Phan Van Tu\""
                                "},"
                                "\"TienDien\":23.000,"
                                "\"TienNuoc\":40.000"
                                "}"
                           "}";

    // Phân tích cú pháp chuỗi JSON
    JsonValue *json_value = parse_json(&json_str);

    test(json_value);

    free_json_value(json_value);



    return 0;
}
