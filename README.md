# Overview
https://github.com/moneyforward/mfid_web/issues/6


When user withdraw from the MFID, the RP side need to prepare an API to confirm whether the user has already withdrawn from the RP's services or not. Any services that use MFID must implement this API.


※ RP: OpenIDConnect terminology: Refers to a service that performs user authentication with MFID.

## API flow
The APIs marked with ★ in figure below are defined in this specification.
```uml
User->MFID: withdrawal operation
MFID->Service A: **★Confirm whether withdrawable or not**
MFID<--Service A: OK
MFID->Service B: **★Confirm whether withdrawable or not**
MFID<--Service B: OK
Note right of MFID: If all services are\nOK then perform withdrawal
MFID->MFID: Withdraw
User<-MFID: Complete withdrawal
```

# Specification

## Things RP side needs to do
* Endpoint URL
    * It is necessary to register the endpoint URL through the RP management screen of MFID

## API
```http
GET https://hoge.moneyforward.com/no_auth/withdrawable?user_id=:user_id HTTP/1.1
```

※ `https://hoge.moneyforward.com/no_auth/withdrawable` is the endpoint URL determined by the RP

### Parameter
|Parameter|Explain|Value|Require|Default|Note|
| --- | --- | --- | --- | --- | --- |
| user_id | User ID | string | Yes | - | ID Token subject value |

### Response
```http
HTTP/1.1 200 OK
Content-Type: application/json

{
  "withdrawable" : true 
}
```

* withdrawable
    * withdrawable -> true
    * Can't withdraw -> false
    * Specified user_id does not exist -> true

# Note
* For services that do not require withdrawal on the RP side when the MFID is withdrawn, it is ok to always return `withdrawable: true` for the implementation
* However、If you withdraw from MFID without withdrawing from the RP side, the following cases will occur.
    * You can no longer sign up for RP with the same ID
    * Data remains on the RP side
* In the future, with the MFID withdrawal as a trigger, event notifications may be sent to each RP, and each RP may perform necessary processing such as data deletion.
