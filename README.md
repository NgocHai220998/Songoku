
## Authorization Code Flow

- [OpenID Configuration Endpoint](#openid-configuration-endpoint)
- [User Registration Endpoint](#user-registration-endpoint)
- [Authorization Endpoint](#authorization-endpoint)
- [Token Endpoint](#token-endpoint)
- [Token Revocation Endpoint](#token-revocation-endpoint)
- [Token Introspection Endpoint](#token-introspection-endpoint)
- [JWKs Endpoint](#jwks-endpoint)
- [UserInfo Endpoint](#userinfo-endpoint)
- [End Session Endpoint](#end-session-endpoint)

### OpenID Configuration Endpoint

- URI: `/.well-known/openid-configuration`
- HTTP Methods: `GET/POST`

#### Parameters

N/A

#### Response

afterward

#### References

- [OpenID Connect Discovery 1.0](https://openid.net/specs/openid-connect-discovery-1_0.html)

### User Registration Endpoint

- URI: `/sign_up`
- HTTP Methods: `GET`

If parameters are valid, even if the user is already logged in to MFID, it will be logged out and the user registration screen will always be displayed. After completing user registration and verifying the identity of the email address, the parameters passed to this endpoint will be inherited and redirected to the authorization endpoint. If the application is auto-authorized (skip authorization), it will be redirected to the specified redirect_uri with code and state.

#### Parameters

Parameter|Required?|Description
---|---|---
client_id|yes|Please specify the Client ID provided at the time of application registration.
redirect_uri|yes|Specify the full URL (or custom URI scheme) that you set when registering your application.
response_type|yes|Specify a string called `code`.
scope|yes|For multiple selection, please separate them with spaces.
state||It is used as a defend against CSRF to confirm that it is the same session. Specify a sufficiently long random string generated by your application for each request.
code_challenge||Used when using PKCE (Mitigating Authorization Code Interception Attacks). Please specify a value generated by the client using a generation method that conforms to RFC 7636.
code_challenge_method||Please specify `code_challenge` when using PKCE as well. You can use `plain` or `S256`.
ui_locales||Specify the language (`ja`/`en`) displayed in MFID

#### Response

Parameter|Required?|Description
---|---|---
code|yes|Authorization code.
state|yes|State value specified at the time of request returned only when the state at the time of ※Authorization request is specified. It is used as a defend against CSRF to check if the state value specified at the time of the request matches the state value obtained in the response.


### Authorization Endpoint

- URI: `/oauth/authorize`
- HTTP Methods: `GET/POST`

#### Parameters

Parameter|Required?|Description
---|---|---
client_id|yes|Please specify the Client ID provided at the time of application registration.
redirect_uri|yes|Specify the full URL (or custom URI scheme) that you set when registering your application.
response_type|yes|Specify a string called `code`.
scope|yes|For multiple selection, please separate them with spaces.
state||It is used as a defend against CSRF to confirm that it is the same session. Specify a sufficiently long random string generated by your application for each request.
code_challenge||Used when using PKCE (Mitigating Authorization Code Interception Attacks). Please specify a value generated by the client using a generation method that conforms to RFC 7636.
code_challenge_method||Please specify `code_challenge` when using PKCE as well. You can use `plain` or `S256`.
unauthenticated_fallback||You can specify which screen will be displayed if the user is not logged in.<br>**signup** : redirect to the user registration screen.<br>If not specified or otherwise, it will redirect to the login screen.
prompt||Specify the action you want the user to take.<br>**login**: Force the login screen to appear. Even if the user is already logged into MFID, it will be logged out.<br>**select_account**: A screen will appear prompting the user to select an account to login.<br/>If you have already logged in, you will be prompted to select `use this account` or `use others account`. If you choose the `use this account` then no re-authentication is required.<br/>If you are not logged in, a screen will appear asking you to select `Login with the last logged in account` or `Login with another account`. If you choose the `Login with the last logged in account`, you will be asked to re-authenticate.
login_hint||Used as a hint for the login identifier. If a user has email address different from the specified value is logged into MFID, a login request will be made again. You can specify an email address for the value. However, that you are not necessarily logged in as a user with this value.
ui_locales||Specify the language (`ja`/`en`) displayed in MFID

#### Response

Parameter|Required?|Description
---|---|---
code|yes|Authorization code.
state|yes|State value specified at the time of request returned only when the state at the time of ※Authorization request is specified. It is used as a defend against CSRF to check if the state value specified at the time of the request matches the state value obtained in the response.

#### References

- [OpenID Connect Core 1.0 - Authorization Endpoint](https://openid.net/specs/openid-connect-core-1_0.html#AuthorizationEndpoint)
- [Proof Key for Code Exchange by OAuth Public Clients](https://tools.ietf.org/html/rfc7636)

### Token Endpoint

This endpoint has two methods ("Get New Access Token" and "Renew Access Token") to get a valid access token.

- URI: `/oauth/token`
- HTTP Methods: `POST`


#### Request headers（When Get New Access Token or Renew Access Token）

This endpoint should authenticate the client using BASIC authentication.
Concatenate the Client ID and Client Secret with a colon (":") and send the Base64-encoded value in the Authorization header.

#### Parameters（When Get New Access Token）

Parameter|Required?|Description
---|---|---
grant_type|yes|Specify a string called `authorization_code`.
client_id|※|Please specify the Client ID provided at the time of application registration.
client_secret|※|Please specify the Client Secret provided at the time of application registration.
code|yes|Specify the authorization code string obtained from the Authorization endpoint. Valid for 10 minutes.
redirect_uri|yes|Specify the full URL (or custom URI scheme) that you set when registering your application.
code_verifier||Used when using PKCE (Mitigating Authorization Code Interception Attacks). Please specify the `code_verifier` used at the time of authorization request.

※ Sending `client_id` and `client_secret` as request parameters is deprecated.Please use it only when the environment does not allow client authentication in the request header. Authentication via request headers is recommended when possible.

#### Response（When Get New Access Token）

Parameter|Required?|Description
---|---|---
access_token|yes|Access token for accessing the API.
token_type|yes|Token Type. Provides the information necessary to properly use the Access Token when accessing the Web API (format: Bearer Token).
expires_in|yes|The number of seconds that represents the Access Token expiration period.
refresh_token|yes|Refresh Token. Used when updating the Access Token.
scope|yes|The scope of the provided access token.
created_at|yes|The date and time when the access token was created.
id_token|yes|ID Token. A signed token for tamper detection that contains user credentials.

#### Parameters（When Renew Access Token）

Parameter|Required?|Description
---|---|---
grant_type|yes|Specify a string called `refresh_token`.
refresh_token|yes|Please specify the Refresh Token obtained when a new access token is provided.
client_id|※|Please specify the Client ID provided at the time of application registration. If client_id is specified, you need to specify also client_secret to avoid error.
client_secret|※|Please specify the Client Secret provided at the time of application registration.

※ Sending `client_id` and `client_secret` as request parameters is deprecated.Please use it only when the environment does not allow client authentication in the request header. Authentication via request headers is recommended when possible.

#### Response（When Renew Access Token）

Parameter|Required?|Description
---|---|---
access_token|yes|Access token for accessing the API.
token_type|yes|Token Type. Provides the information necessary to properly use the Access Token when accessing the Web API (format: Bearer Token).
expires_in|yes|The number of seconds that represents the Access Token expiration period.
refresh_token|yes|Refresh Token. Used when updating the Access Token.
scope|yes|The scope of the provided access token.
created_at|yes|The date and time when the access token was created.
id_token|yes|ID Token. A signed token for tamper detection that contains user credentials.

#### References

- [OpenID Connect Core 1.0 - Token Endpoint](https://openid.net/specs/openid-connect-core-1_0.html#TokenEndpoint)

### Token Revocation Endpoint

- URI: `/oauth/revoke`
- HTTP Methods: `POST`

#### Request headers（When Get New Access Token or Renew Access Token）

This endpoint should authenticate the client using BASIC authentication.
Concatenate the Client ID and Client Secret with a colon (":") and send the Base64-encoded value in the Authorization header.

#### Parameters

Parameter|Required?|Description
---|---|---
client_id|※|Please specify the Client ID provided at the time of application registration.
client_secret|※|Please specify the Client Secret provided at the time of application registration.
token|yes|Please specify the access token or refresh token you want to invalidate.

※ Sending `client_id` and `client_secret` as request parameters is deprecated.Please use it only when the environment does not allow client authentication in the request header. Authentication via request headers is recommended when possible.

#### Response

※ returns empty json

#### References

- [RFC7009 OAuth 2.0 Token Revocation](https://tools.ietf.org/html/rfc7009)

### Token Introspection Endpoint

- URI: `/oauth/introspect`
- HTTP Methods: `POST`

#### Request headers（When Get New Access Token or Renew Access Token）

This endpoint should authenticate the client using BASIC authentication.
Concatenate the Client ID and Client Secret with a colon (":") and send the Base64-encoded value in the Authorization header.

#### Parameters

Parameter|Required?|Description
---|---|---
client_id|※|Please specify the Client ID provided at the time of application registration.
client_secret|※|Please specify the Client Secret provided at the time of application registration.
token|yes|Please specify the access token to be checked.

※ Sending `client_id` and `client_secret` as request parameters is deprecated.Please use it only when the environment does not allow client authentication in the request header. Authentication via request headers is recommended when possible.

#### Response

Parameter|Required?|Description|Sample
---|---|---|---
active|yes|Validity of the specified access token.|true
scope||The scope of the specified access token.|"openid email profile address"
client_id||Client ID for the specified access token.|"bcdeb0f1b654"
token_type||The type of the specified access token.|"Bearer"
exp||Time at which the specified access token expires.(UNIX time)|1539251579
iat||The time when the specified access token was provided.（UNIX time)|1539244379
sub||The user identifier of the resource owner for the specified access token.|"12345"

#### References

- [RFC7662 OAuth 2.0 Token Introspection](https://tools.ietf.org/html/rfc7662)

### JWKs Endpoint

- URI: `/oauth/discovery/keys`
- HTTP Methods: `GET`

#### Parameters

N/A

#### Response

Parameter|Description
---|---
keys|An array of JWK values.
kid|Key ID contained in the header of the ID Token.
e|exponent. Encryption index to recover the Public Key.
n|modulus. The absolute value of the public key to restore the public key.
use|Purpose of using public key. "sig" stands for signature, indicating that it is provided for signature verification purposes.
alg|Algorithm for signature verification


### UserInfo Endpoint

- URI: `/oauth/userinfo`
- HTTP Methods: `GET/POST`

#### Request headers

field|Required?|Description
---|---|---
Authorization|yes|Please specify the Access Token string（format: Bearer Token）

#### Parameters

Parameter|Required?|Description
---|---|---
access_token|yes|Please specify the Access Token string

#### Response

Parameters|Description|Required scope|Sample
---|---|---|---
sub|user identifier|openid|"abcde"
identification_code|（Send to external service）user identifier\[12 digits\]|openid|"123456789012"
email|email address|email|"moneyforward@example.com"
email_verified|Email verified status|email|true
gender|sex|profile|"male"
birthdate|year of birth（Does not include month and day）|profile|"1986"
address|-|-|-
postal_code|post code|address|"1080023"
region|prefectures|address|"東京都"


#### References

- [OpenID Connect Core 1.0 - UserInfo Endpoint](https://openid.net/specs/openid-connect-core-1_0.html#UserInfo)


### End Session Endpoint

- URI: `/end_session`
- HTTP Methods: `GET`

If the parameters are valid, even if the user is already logged into MFID, it will be logged out and redirected to the specified URL (post_logout_redirect_uri). Use this if you want to log out the OP when you log out the RP.

#### Parameters

Parameter|Required?|Description
---|---|---
client_id|yes|Please specify the Client ID provided at the time of application registration.
post_logout_redirect_uri|yes|Specify the full URL (or custom URI scheme) that you set when registering your application.

#### References

- [OpenID Connect Session Management 1.0 - RP-Initiated Logout](https://openid.net/specs/openid-connect-session-1_0.html#RPLogout)
