[@react.component]
let make = () => {
    let (show, setShow) = React.useState(() => false);

    <div id="create-dialog-button-container" >
        <CreateButton setShow={setShow} />
        {
            if (show) {
                <CreateDialog setShow={setShow} />
            } else {
                <div></div>
            };
        }
    </div>
}
