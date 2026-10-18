#version 330 core
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

    // Luz tipo reflector para el farol
struct SpotLight
{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

// POINTLIGHT - FOGATA
struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// DIRLIGHT - QUINTA FUENTE

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform Light light2;
uniform SpotLight spotLight;
uniform PointLight pointLightFogata;
uniform DirLight dirLight;
uniform sampler2D texture_diffuse1;

void main()
{
    // Ambient
    vec3 ambient = light.ambient *material.diffuse;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    // Ambient 2
    vec3 ambient2 = light2.ambient * material.diffuse;

    // Diffuse 2
    vec3 lightDir2 = normalize(light2.position - FragPos);
    float diff2 = max(dot(norm, lightDir2), 0.0);
    vec3 diffuse2 = light2.diffuse * diff2 * material.diffuse;

    // Specular 2
    vec3 reflectDir2 = reflect(-lightDir2, norm);
    float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0), material.shininess);
    vec3 specular2 = light2.specular * (spec2 * material.specular);

    // Sumamos todo
    vec3 result = (ambient + diffuse + specular) + (ambient2 + diffuse2 + specular2);
    // SPOTLIGHT - FAROL
// ======================================

// Direccion desde el fragmento hacia la luz
vec3 spotDir = normalize(spotLight.position - FragPos);

// Angulo del cono de luz
float theta = dot(spotDir, normalize(-spotLight.direction));

// Suavidad del borde del cono
float epsilon = max(spotLight.cutOff - spotLight.outerCutOff, 0.0001);
float intensidad = clamp(
    (theta - spotLight.outerCutOff) / epsilon,
    0.0,
    1.0
);

// Distancia entre la luz y el fragmento
float distancia = length(spotLight.position - FragPos);

// Atenuacion de la luz
float atenuacion = 1.0 / (
    spotLight.constant +
    spotLight.linear * distancia +
    spotLight.quadratic * distancia * distancia
);

// Componente ambiental
vec3 ambientSpot = spotLight.ambient;

// Componente difusa
float diffSpot = max(dot(norm, spotDir), 0.0);
vec3 diffuseSpot = spotLight.diffuse * diffSpot;

// Componente especular
vec3 reflectSpot = reflect(-spotDir, norm);
float specSpot = pow(
    max(dot(viewDir, reflectSpot), 0.0),
    material.shininess
);

vec3 specularSpot = spotLight.specular * specSpot;

// Iluminacion total del farol
vec3 resultadoSpot = (
    ambientSpot +
    diffuseSpot +
    specularSpot
) * intensidad * atenuacion;

// Agregar la luz del farol a las del Sol y la Luna
// Conservar la iluminacion del farol
result += resultadoSpot;

// ======================================
// POINTLIGHT - FOGATA
// ======================================

// Vector desde el fragmento hacia la fogata
vec3 dirFogata = normalize(pointLightFogata.position - FragPos);

// Distancia a la fogata
float distanciaFogata = length(pointLightFogata.position - FragPos);

// Atenuacion con la distancia
float atenuacionFogata = 1.0 / (
    pointLightFogata.constant +
    pointLightFogata.linear * distanciaFogata +
    pointLightFogata.quadratic * distanciaFogata * distanciaFogata
);

// Iluminacion ambiental
vec3 ambienteFogata = pointLightFogata.ambient * material.diffuse;

// Iluminacion difusa
float difFogata = max(dot(norm, dirFogata), 0.0);
vec3 difusaFogata =
    pointLightFogata.diffuse * difFogata * material.diffuse;

// Iluminacion especular
vec3 reflejoFogata = reflect(-dirFogata, norm);

float brilloFogata = pow(
    max(dot(viewDir, reflejoFogata), 0.0),
    material.shininess
);

vec3 especularFogata =
    pointLightFogata.specular *
    brilloFogata *
    material.specular;

// Iluminacion total de la fogata
vec3 resultadoFogata = (
    ambienteFogata +
    difusaFogata +
    especularFogata
) * atenuacionFogata;

// Sumar las cuatro fuentes de luz
result += resultadoFogata;

// ======================================
// ILUMINACION DIRECCIONAL
// ======================================

// Direccion desde la superficie hacia la luz
vec3 dirLuz = normalize(-dirLight.direction);

// Luz ambiental
vec3 ambienteDir = dirLight.ambient * material.diffuse;

// Luz difusa
float difDir = max(dot(norm, dirLuz), 0.0);

vec3 difusaDir =
    dirLight.diffuse * difDir * material.diffuse;

// Luz especular
vec3 reflejoDir = reflect(-dirLuz, norm);

float brilloDir = pow(
    max(dot(viewDir, reflejoDir), 0.0),
    material.shininess
);

vec3 especularDir =
    dirLight.specular * brilloDir * material.specular;

// Sumar la quinta fuente
result += ambienteDir + difusaDir + especularDir;

// Mantener la textura original
color = vec4(result, 1.0f) * texture(texture_diffuse1, TexCoords);

}

