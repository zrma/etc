module Main exposing (main)

import Browser
import Html exposing (Html, button, div, text)
import Html.Attributes exposing (style)
import Html.Events exposing (onClick)
import String

main : Program () Int Msg
main =
    Browser.sandbox { init = 0, update = update, view = view }

type Msg = Increment | Decrement

update : Msg -> Int -> Int
update msg model =
    case msg of
        Increment ->
            model + 1

        Decrement ->
            model - 1

view : Int -> Html Msg
view model =
    div [ style "display" "flex", style "flex-direction" "column", style "align-items" "center", style "justify-content" "center", style "height" "100vh", style "background-color" "#f7f7f7" ]
        [ button [ style "background-color" "#007bff", style "border" "none", style "color" "white", style "padding" "15px 32px", style "text-align" "center", style "text-decoration" "none", style "display" "inline-block", style "font-size" "16px", style "margin" "4px 2px", style "cursor" "pointer", style "border-radius" "50%", onClick Decrement ] [ text "-" ]
        , div [ style "font-size" "24px", style "font-weight" "bold", style "margin" "20px" ] [ text (String.fromInt model) ]
        , button [ style "background-color" "#28a745", style "border" "none", style "color" "white", style "padding" "15px 32px", style "text-align" "center", style "text-decoration" "none", style "display" "inline-block", style "font-size" "16px", style "margin" "4px 2px", style "cursor" "pointer", style "border-radius" "50%", onClick Increment ] [ text "+" ]
        ]
