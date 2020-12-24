
stock randomEx(min, max)
{
    new rand = random(max) + min;
    return rand;
}

stock Float:Distance(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2) {
    return VectorSize(x1 - x2, y1 - y2, z1 - z2);
}

stock GetXYBehindOfVehicle(vehicleid, &Float:x, &Float:y, Float:distance) {
    new
        Float:a;
    GetVehiclePos(vehicleid, x, y, a);
    GetVehicleZAngle(vehicleid, a);
    x += (distance * floatsin( -a + 180, degrees));
    y += (distance * floatcos( -a + 180, degrees));
}