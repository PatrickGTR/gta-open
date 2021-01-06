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
    GivePlayerMoney(playerid, -House_GetPrice(houseid));
    SendServerMsgF(playerid, "Congratulations! You have bought the house for "C_GREEN"$%i", House_GetPrice(houseid));
    House_Buy(playerid, houseid);
    return 1;
}

CMD:hdescription(playerid, params[]) {
    if(isnull(params)) {
        return SendErrorMsg(playerid, "/hdescription <new description>");
    }

    new
        houseid = Player_GetInHouseID(playerid);

    if(!Player_IsInsideHouse(playerid)) {
        return SendErrorMsg(playerid, "You need to be inside a house you own.");
    }

    if(!House_PlayerIsOwner(playerid, houseid)) {
        return SendErrorMsg(playerid, "You do not own this house.");
    }

    new
        ret = House_UpdateDescription(playerid, houseid, params);
    if(!ret) {
        return SendErrorMsg(playerid, "Descrption must not have more than 32 characters.");
    }

    SendServerMsgF(playerid, "You have successfully changed your house description to "C_GREY"%s", params);
    return 1;
}


ACMD:[4]hcreate(playerid, params[])
{
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

    new
        ret = House_Create(
        x,
        y,
        z,
        a,
        price,
        interior,
        .save = true
    );

    if(ret == -1) {
        return SendErrorMsg(playerid, "Can't create more houses, please increase the size of MAX_HOUSES");
    }
    return true;
}

ACMD:[4]hdelete(playerid, params[]) {

    if(isnull(params)) {
        return SendErrorMsg(playerid, "/hdelete <house id>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "invalid input.");
    }

    new
        houseid = strval(params);

    House_Delete(playerid, houseid);
    return 1;
}