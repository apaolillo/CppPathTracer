#include <fileformats/obj.h>
#include <hitables/triangle.h>

#include <materials/metal.h>
#include <materials/pbr.h>

static void splitAtChar(std::string &line, std::vector<std::string> &parts, char split)
{
    parts.clear();

    std::string buf;
    for (char c : line)
    {
        if (c == split)
        {
            parts.push_back(buf);
            buf.clear();
        }
        else
            buf += c;
    }
    if (buf.size())
        parts.push_back(buf);
}

Point3 Obj::parseVec(const std::vector<std::string> &parts, int start_index) const
{
    // @todo: Test if the x y and z values are actually valid
    std::string::size_type size;
    double x = std::stod(parts[start_index + 0], &size);
    double y = std::stod(parts[start_index + 1], &size);
    double z = std::stod(parts[start_index + 2], &size);

    return Point3(x, y, z);
}

Point3 Obj::getVert(const std::string vert) const
{
    // @todo: this is a little clunky
    std::string s;
    int idx = vert.find('/');
    if (idx)
        s = vert.substr(0, idx);
    else
        s = vert;

    // @todo: check bounds to make sure we actually have this index

    // Vertex indices start at 1
    return m_verts[std::stoi(s) - 1];
}

void Obj::read(Scene &scene)
{
    HitableList &list = scene.getHitableList();

    // auto defmat = std::make_shared<Metal>(Color(0.9,0.9,0.9), 0.5);
    // auto defmat = std::make_shared<Lambertian>(std::make_shared<UVTexture>());
    auto defmat = std::make_shared<PBR>(std::make_shared<SolidColor>(0.8, 0.1, 0.1), 1, 0, 0, std::make_shared<SolidColor>(0), 0);

    if (!m_infile.is_open())
    {
        WARN("Returning empty HitableList.");
        return;
    }

    std::string line;
    std::vector<std::string> parts;
    parts.reserve(5); // most will not be larger than this so we reduce size increases.
    while (!m_infile.eof())
    {
        std::getline(m_infile, line);

        // Skip over comments and empty lines
        if (line.size() == 0 || line.front() == '#')
            continue;

        // Split the line into parts by space since this is makes the whole thing easier
        // to parse
        splitAtChar(line, parts, ' ');

        // @todo: make sure the parts vector is actually large enough for vector parsing
        if (parts.front() == "v")
        {
            m_verts.push_back(parseVec(parts, 1));
        }
        else if (parts.front() == "f")
        {
            auto triangle = new Triangle(getVert(parts[1]), getVert(parts[2]), getVert(parts[3]), defmat);
            list.add(triangle);
        }
    }
}