open ReactNative;

let styles = Style.(StyleSheet.create({"text": style(~color="red", ())}));

[@react.component]
let make = () => {
  let send = Store.useDispatch();
  let counter = Store.useSelector(state => state.counter);
  <View>
    <Text>
      {{
         string_of_int(counter);
       }
       ->React.string}
    </Text>
    <Button title="Decrement" onPress={_ => send(`Decrement)} />
    <Button title="Increment" onPress={_ => send(`Increment)} />
  </View>;
};
