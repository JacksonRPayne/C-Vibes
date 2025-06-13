import os
import json

project_dir = "C:/Code/C Vibes"
src_dir = os.path.join(project_dir, "src")
main_command = "gcc -Wall -Isrc -include src/unityBuild.h -o main.exe src/main.c -lglfw3dll -lopengl32"

entries = []

# Recursively walk through src_dir and subdirectories
for root, _, files in os.walk(src_dir):
    for filename in files:
        if filename.endswith(".c"):
            file_path = os.path.join(root, filename).replace("\\", "/")
            entries.append({
                "directory": project_dir,
                "command": main_command,
                "file": file_path
            })

# Write to compile_commands.json
output_path = os.path.join(project_dir, "compile_commands.json")
with open(output_path, "w") as f:
    json.dump(entries, f, indent=2)
