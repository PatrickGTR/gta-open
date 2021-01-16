stock LoadStaticVehiclesFromFile(const filename[])
{
    new
        line[55],
        File:file_ptr,
        vehicletype,
        Float:SpawnX,
        Float:SpawnY,
        Float:SpawnZ,
        Float:SpawnRot,
        col1,
        col2,
        vehicles_loaded;

    file_ptr = fopen(filename, filemode:io_read);

    if (!file_ptr) return 0;

    vehicles_loaded = 0;

    while(fread(file_ptr, line, sizeof(line)) > 0)
    {
        sscanf(line, "p<,>iffffii", vehicletype, SpawnX, SpawnY, SpawnZ, SpawnRot, col1, col2);

        if (vehicletype < 400 || vehicletype > 611) {
            continue;
        }

        AddStaticVehicleEx(vehicletype, SpawnX, SpawnY, SpawnZ, SpawnRot, col1, col2, (60*60)); // respawn 60 minutes
        vehicles_loaded ++;
    }
    fclose(file_ptr);
    printf("Loaded %d vehicles from: %s", vehicles_loaded, filename);
    return vehicles_loaded;
}

stock IsVehiclePolice(vehicleid) {
	new
        model = GetVehicleModel(vehicleid);

    switch(model) {
        case 425, 520, 497, 470, 432, 428, 523, 427, 490, 601: {
            return 1;
        }
        case 596 .. 599: {
            return 1;
        }
        default:
            return 0;

    }
    return 0;
}