CMD:buyhouse(playerid, params[]) {
    new 
        houseid = Player_GetInHouseID(playerid);

    if(!Player_InHouseEntrance(playerid, houseid)) {
        return SendErrorMsg(playerid, "You are not in any house entrances.");
    }

    if(House_HasOwner(houseid)) {
        return SendErrorMsg(playerid, "This house is already owned by someone else.");
    }

    if(GetPlayerMoney(playerid) < House_GetPrice(houseid)) {
        return SendErrorMsg(playerid, "You don't have enough money to buy this house.");
    }

    if(Player_GetTotalHouses(playerid) >= MAX_HOUSES_PER_PLAYER) {
        return SendErrorMsg(playerid, "You reached the limit of houses you can own.");
    }

    House_Buy(playerid, houseid);
    GivePlayerMoney(playerid, -House_GetPrice(houseid));
    return 1;
}


ACMD:[4]hcreate(playerid, params[])
{
    if (House_GetTotal() == MAX_HOUSES)
        return SendErrorMsg(playerid, "MAX_HOUSES reached its limit.");

    new 
        price, 
        interior;

    if(sscanf(params, "ii", price, interior)) {
        return SendSyntaxMsg(playerid, "/hcreate <price> <interior id>");
    }
    
    if(!(0 <= interior < House_GetInteriorArraySize())){
        return SendErrorMsgF(playerid, "Please insert a value between 0 and %i", House_GetInteriorArraySize());
    }


    new 
        Float:x,
        Float:y,
        Float:z,
        Float:a;

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    House_Create(
        x, 
        y, 
        z,
        a,
        GetPlayerVirtualWorld(playerid),
        price,
        interior
    );

    return true;
}