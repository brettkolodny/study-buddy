[@react.component]
let make = () => {
    let (cards, setCards) = React.useState(() => []);

    <div id="create-dialog-container">
        <div id="create-dialog">
            <div id="create-dialog-topbar">
                <div id="create-dialog-exit">
                </div>
            </div>
            <div id="create-dialog-button-container">
                <div className="create-dialog-button"></div> 
                <div className="create-dialog-button"></div> 
            </div>
        </div>
    </div>
}